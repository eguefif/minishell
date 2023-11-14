import subprocess
import os
import pytest

CC = "gcc "
CFLAGS = "-g -Wall -Werror -Wextra "
INC = "-I../includes -I../lib/libft/includes -I../lib/readline-8.2 "
LIB = "-L./unit_tests -lminishell -L../lib/libft -lft "
# LIB = "-L../lib/libft -lft -lncurses -L../lib/readline-8.2 -lreadline "

def build_test(path):
    if not os.path.isdir(path):
        return False
    for file in os.listdir(path):
        if file.find(".c") != -1 and file.find(".swp") == -1:
            if not (os.path.isdir("./unit_tests/binary")):
                os.mkdir("./unit_tests/binary")
            target = " ./unit_tests/binary/" + file.strip(".c") + " "
            cmd = CC + "-o " + target + "./unit_tests/" + file + " "  + CFLAGS + INC + LIB 
            print(cmd)
            try:
                retval = subprocess.run(cmd.split(), capture_output = True, text = True, timeout = 2)
            except subprocess.TimeoutExpired:
                print("Timeout: ", file)
                continue
            if retval.returncode != 0 or retval.stdout.find("error") != -1:
               return 1
    return 0

def get_binaries(path):
    if not os.path.isdir(path):
        return False
    retval = []
    for file in os.listdir(path):
        if file.find(".") == -1:
            retval.append(file)
    return retval

if build_test("./unit_tests/") == 1:
    print("\033Compilation error")
    exit(1)
arr = get_binaries("./unit_tests/binary")

@pytest.mark.parametrize("binary", arr)
def test_unit(binary):
    cmd = "./unit_tests/binary/" + binary
    try:
        retval = subprocess.run(cmd, capture_output = True, text = True, timeout = 2)
    except subprocess.TimeoutExpired:
        print("Timeout: ", file)
        retval = 0
    assert retval and retval.stdout.find("Error") == -1 and retval.returncode == 0
