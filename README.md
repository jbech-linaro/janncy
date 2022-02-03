# janncy

## Installation

### Clone the repository
Use the `--recurse-submodules` flag to get all the submodules:
```bash
$ git clone --recurse-submodules git@github.com:n-samar/janncy.git
#
# If you're working on a specific branch, instead run
# git clone -b <my-branch> --recurse-submodules git@github.com:n-samar/janncy.git
```

Alternatively, you can clone and install the submodules in two steps:
```bash
$ git clone git@github.com:n-samar/janncy.git
$ cd janncy
$ git submodule update --init --recursive
```

### `./install.sh`
On Ubuntu, you can install all required OS and Python packages using:
```bash
./install.sh [-v]
```

As the script uses `sudo apt-get` to install OS packages, you might be prompted
to enter a password. `APT_PKGS` contains the list of packages to be installed.

If you include `-v`, the script will create a [Python virtual
environment][venv], and install all Python packages in it. This has the benefit
of creating a separate copy of all of janncy's Python dependencies that does not
interfere with any other Python scripts on your machine. However, it requires
activating the virtual environment before running subsequent build commands
(once per shell):
```bash
$ source .pyvenv/bin/activate
```

### Compiling Libraries
Some of the C++ libraries janncy uses (`NTL`, `googletest`, `HEANN`, and `onnx`)
are included as git submodules and have to be compiled from source. We have
added a target in our build system, [SConstruct][scons], that performs this
automatically:
```bash
$ scons deps
```

### Compile janncy
```bash
$ scons
```

## Development

## Running the test cases
Once everything has been compiled, there is should have been a test binary
produced, to run that, do:
```bash
$ ./build/tests
```

### Updating git submodules
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
These commands might later on be wrapped in a helper function in SConstruct or
as a separate update script to make it easier to do the updates.


### Pre-Commit Hooks
Install [pre-commit], and set it up to run automatically on before commits using
```bash
$ pre-commit install
```
To manually run the hooks on all files (e.g., if you change them) use
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

[clang-format-vimrc]: https://github.com/n-samar/.config/blob/master/nvim/init.vim#L126-L128
[clang-format]: https://clang.llvm.org/docs/ClangFormat.html
[google-cpp]: https://google.github.io/styleguide/cppguide.html
[pre-commit]: https://pre-commit.com/
[venv]: https://docs.python.org/3/tutorial/venv.html
[scons]: https://scons.org/
[vim-clang-format]: https://github.com/rhysd/vim-clang-format
