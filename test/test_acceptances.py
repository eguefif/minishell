from typing import List
import subprocess
import pytest
import os


MINISHELL = "../minishell"


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

@pytest.mark.parametrize("script", acc)
def test_acceptances(script):
    bash_output = subprocess.run("bash", input=script, capture_output=True, text=True)
    minishell_output = subprocess.run(MINISHELL, input=script, capture_output=True, text=True, shell=True)
    assert bash_output.stdout == minishell_output.stdout
