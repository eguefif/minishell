import re
from typing import List 
import subprocess
import pytest
import os


MINISHELL = "./minishell"

with open("commands.tsv", "r") as f:
    content = f.read()

segfault_test = content.split("\n")

@pytest.mark.parametrize("command", segfault_test)
def test_segfault(command):
    try:
        retval = subprocess.run("./minishell", input=command, capture_output=True, text=True, timeout=5)
    except subprocess.TimeoutExpired:
        print("Error: timeout")

    print(retval)
    assert retval.returncode != -11
