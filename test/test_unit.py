import subprocess
import os
import pytest

CC = "gcc "
CFLAGS = "-g -Wall -Werror -Wextra "
INC = "-I../includes -I../lib/libft/includes -I../lib/readline-8.2 "
LIB = "-L./unit_tests -lminishell -L../lib/libft -lft"
# LIB = "-L../lib/libft -lft -lncurses -L../lib/readline-8.2 -lreadline "

def build_test(path):
    if not os.path.isdir(path):
        return False
    for file in os.listdir(path):
        if file.find(".c") != -1 and file.find(".swp") == -1:
            cmd = CC + "-o " + path + file.strip(".c") + " " + path + file + " " + CFLAGS + INC + LIB 
            print(cmd)
            try:
                retval = subprocess.run(cmd.split(), capture_output = True, text = True, timeout = 2)
            except subprocess.TimeoutExpired:
                print("Timeout: ", file)
                continue
            if retval.returncode != 0:
               print("Could not compile ", file, retval.stdout + retval.stderr)

def get_binaries(path):
    if not os.path.isdir(path):
        return False
    retval = []
    for file in os.listdir(path):
        if file.find(".") == -1:
            retval.append(file)
    return retval

build_test("./unit_tests/")
arr = get_binaries("./unit_tests/")

@pytest.mark.parametrize("binary", arr)
def test_unit(binary):
    cmd = "./unit_tests/" + binary
    try:
        retval = subprocess.run(cmd, capture_output = True, text = True, timeout = 2)
    except subprocess.TimeoutExpired:
        print("Timeout: ", file)
        retval = 0
    assert retval and retval.stdout.find("Error") == -1 and retval.returncode == 0
