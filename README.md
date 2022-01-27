# janncy
This is a development environment for Fully Homomorphic Encryption (FHE)
research where emphasis is on `CKKS`.


## Installation
This setup has been built for and been tested with Ubuntu. The setup relies on a
couple of distro packages as well as a couple of Python packages. This step is
meant to be done once or at least very infrequently.

### Get the source code
First step is to clone the code and get all submodules. With a more recent
version of git, all can be done in one go.
```bash
$ git clone --recurse-submodules git@github.com:n-samar/janncy.git
#
# If you're working on a certain branch, run this instead
# git clone -b <my-branch> --recurse-submodules git@github.com:n-samar/janncy.git
```

If you're running an older version of git, then do as follows:
```bash
$ git clone git@github.com:n-samar/janncy.git
$ cd janncy
$ git submodule update --init --recursive
```

### Install dependencies

**apt-packages:**

All necessary packages can be installed by running the provided `install.sh`
script. Since the script will try to install packages for Ubuntu, the script
will ask for the `sudo` password. To see the list of packages it will try to
install, please see the `APT_PKGS` variable in the script.

**python-packages:**

There are two ways to install the Python packages. One is into the OS/distro
itself, that is what happens when running `install.sh` **without** providing any
parameters. The other alternative is to install all Python packages into a
virtual python environment. This is achieved by providing `-v` to the
install-script. The benefits with the latter is that it puts and deals with all
Python dependencies that `janncy` has into a single folder. Which means that it
doesn't interfere with other Python scripts on your Linux machine. This is the
preferred way.

**Alternative 1 - installing to the OS**
```bash
$ ./install.sh
```

**Alternative 2 -  installing to a virtual Python environment**
```bash
$ ./install.sh -v
```

## Compile janncy
`janncy` leverage the `scons` build tool to compile and link binaries, so all
build related configuration takes place in the `SConstruct` file. Depending on
how you installed the necessary packages you will have to run it slightly
different.

**Python dependencies installed to the OS**
```bash
$ scons
```
or

**Python dependencies installed to a virtual Python environment**
```bash
# The sourcing is only necessary to do "once" per "session/shell".
$ source .pyvenv/bin/activate
$ scons
```

**Local libraries and header files**

Note that besides `janncy` itself, there are a couple of other dependencies like
for example, `NTL`, `googletest`, `HEANN` and `onnx`. For the ones where we
don't expect to do a lot of changes, we've wrapped them under the compile time
argument `deps`. It's necessary to compile these at least once so that all
libraries and headers files can be found when compiling `janncy` itself.
```bash
$ scons deps
```


## Running the test cases
Once everything has been compiled, there is should have been a test binary
produced, to run that, do:
```bash
$ ./build/tests
```

## Git and source code management
The janncy setup uses `git submodules`. Whenever you need to update the
submodules, do as follows:
```bash
# Update all submodules
$ git submodule foreach 'git submodule update --remote --merge'
# Add them to the index
$ git add googletest
$ ...
# Commit the changes
$ git commit -m "Updating submodules"
# Push changes upstream so other can see them
$ git push <remote> <branch>
```
These commands will probably be wrapped in a helper function later on in
SConstruct or as a separate update script to make it easier to do the updates.


## Coding guidelines
### Pre-Commit Hooks
Install [pre-commit] to automatically run the pre-commit hooks before
committing. To run the hooks manually, use
```bash
$ pre-commit run --all-files
```

### Style and Formatting
We defer all formatting and style decisions to the [Google C++ Style
Guide][google-cpp].

We use [clang-format] for C++ code formatting. Clang-format should be executed
automatically by a pre-commit hook.

Additionally, if you use `vim`, you can [configure it][clang-format-vimrc] to
run clang-format when a C++ file is saved. The linked configuration uses
[rhysd/vim-clang-format][vim-clang-format], and follows the rules specified in
`.clang-format` (and doesn't run if `.clang-format` doesn't exist).

You can also try running a clang-tidy check via `scripts/clang-tidy.sh` from the
root of the repository, but that's not yet super reliable.

[pre-commit]: https://pre-commit.com/
[google-cpp]: https://google.github.io/styleguide/cppguide.html
[clang-format]: https://clang.llvm.org/docs/ClangFormat.html
[clang-format-vimrc]: https://github.com/n-samar/.config/blob/master/nvim/init.vim#L126-L128
[vim-clang-format]: https://github.com/rhysd/vim-clang-format
