import re
from typing import List 
import subprocess
import pytest
import os


MINISHELL = "./minishell"


# Regression tests

@pytest.mark.parametrize("script", acc)
with open("commands.tsv", "r") as f:
    content = f.read()

commands = content.split("\n")

@pytest.mark.parametrize("command", commands)
def test_acceptances(command):
    try:
        retval = subprocess.run("./minishell", input=command, capture_output=True, text=True, timeout=5)
    except subprocess.TimeoutExpired:
        print("Error: timeout")
    try:
        bash_output = subprocess.run("bash", input=command, capture_output=True, text=True, timeout=5)
    except subprocess.TimeoutExpired:
        print("Error: timeout")

    print("Minishell:\n",  retval, "bash:\n", bash_output)
    assert bash_output == retval

# Memory check
def get_kind_of_memory_loss(memory_type: str, report: str) -> str:
    retval = re.search(f"{memory_type}: [0-9]", report)
    if not retval:
        return (0)
    retval = re.search("[0-9]", retval.group(0))
    return (int(retval.group(0)))

def is_memory_lost(report):
    if report is None:
        exit(1)
    definitely_lost = get_kind_of_memory_loss("definitely lost", report)
    indirectly_lost = get_kind_of_memory_loss("indirectly lost", report)
    possibly_lost = get_kind_of_memory_loss("possibly lost", report)
    still_reach = get_kind_of_memory_loss("still reachable", report)
    if definitely_lost != 0 or indirectly_lost !=  0 or possibly_lost != 0 or still_reach != 0:
        print("\033[0;31m Memory test failed for:")
        print(report)
        print("\033[0;", end="")
        return 0
    else:
        return 1

memory_command = ["echo salut | grep m | wc -l", "cat salut"]
    
@pytest.mark.parametrize("script", memory_command)
def memory_acceptances(script):
    exe = "valgrind --tool=memcheck --leak-check=full --track-origins=yes -s --show-leak-kinds=all --suppressions=supp.txt " + MINISHELL
    try:
        minishell_output = subprocess.run(exe.split(), input=script, capture_output=True, text=True, timeout=3)
    except subprocess.TimeoutExpired:
        print("Error: timeout")
    
    assert is_memory_lost(minishell_output.stdout + minishell_output.stderr) == 1

