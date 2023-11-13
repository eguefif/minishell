import re
from typing import List 
import subprocess
import pytest
import os


MINISHELL = "./minishell"


def check_path(path: str) -> bool:
    if path[0] == "." and path.find("/") == -1:
        return False
    if len(path) == 0:
        return False
    if not os.path.exists(path):
        return False
    return True

def get_acceptance_file_list(path: str) -> List[str]:
    retval: List[str] = []
    if not check_path(path):
        print("Error: path incorrect: ", path)
        return
    for file in os.listdir(path):
        if file.find(".sh") != -1:
            retval.append(os.path.join(path, file))
    return retval

acc: List[str] = get_acceptance_file_list("./acceptance_scripts/")
if not acc:
    print("Error with getting scripts files")
    exit(1)

# Regression tests

@pytest.mark.parametrize("script", acc)
def test_acceptances(script):
    with open(script, "r") as f:
        content = f.read()
    bash_output = subprocess.run("bash", input=content, capture_output=True, text=True)
    minishell_output = subprocess.run(MINISHELL, input=content, capture_output=True, text=True)
    assert bash_output.stdout == minishell_output.stdout


# Memory check
def get_kind_of_memory_loss(memory_type: str, report: str) -> str:
    retval = re.search(f"{memory_type}: [0-9]", report)
    retval = re.search("[0-9]", retval.group(0))
    return (retval.group(0))

def is_memory_lost(report):
    if report is None:
        exit(1)
    definitely_lost = get_kind_of_memory_loss("definitely lost", report)
    indirectly_lost = get_kind_of_memory_loss("indirectly lost", report)
    possibly_lost = get_kind_of_memory_loss("possibly lost", report)
    still_reach = get_kind_of_memory_loss("still reachable", report)
    if definitely_lost != 0 or indirectly_lost !=  0 or possibly_lost != 0 or  still_reach != 0:
        print(report)
        return 1
    else :
        return 0
    
@pytest.mark.parametrize("script", acc)
def acceptances(script):
    with open(script, "r") as f:
        content = f.read()
    exe = "valgrind --tool=memcheck --leak-check=full --track-origins=yes -s --show-leak-kinds=all " + MINISHELL
    minishell_output = subprocess.run(exe.split(), input=content, capture_output=True, text=True, shell=True)
    
    assert is_memory_lost(minishell_output.stdout + minishell_output.stderr) == 1
