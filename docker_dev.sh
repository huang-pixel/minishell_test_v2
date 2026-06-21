#!/bin/bash
docker run -it --rm \
    -v $(pwd):/minishell \
    -w /minishell \
    fedora:latest \
    bash

## dnf install -y gcc make readline-devel
## dnf install -y valgrind