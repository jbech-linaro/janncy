# janncy
This is a development environment for Fully Homomorphic Encryption (FHE) where
emphasis is on `CKKS`.


## Installation
This setup has been built for and been tested with Ubuntu. The setup relies on a
couple of distro packages as well as a couple of Python packages. This step is
meant to be done once or at least very infrequently.

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

## Run
`janncy` leverage the `scons` build tool to compile and link binaries, so all
build related configuration takes place in the `SConstruct` file. Depending on
how you installed the necessary packages you run it slightly different.

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

Note that besides `janncy` itself, there are a couple of other dependencies like
for example, `NTL`, `googletest`, `HEANN` and `onnx`. Those are typically
compiled once, i.e., the first time running the `scons`. But on subsequent runs
they are typically not recompiled.


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
