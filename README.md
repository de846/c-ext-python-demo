This was a really illuminating project of getting into Python.h under the hood.

To use, run something like:
```
python3 setup.py install
python3 -c "import fputs;\
    fputs.fputs('Written from Python by C!', 'tmp.txt');\
    print(f'''I'm a Macro: {fputs.C_MACRO}''');\
    print(f'''I'm a Constant: {fputs.C_INT_CONSTANT}''');"
```

Running the `setup` module calls `Extension` to compile the targeted `fputs_module.c`, which defaults to `clang` and falls back to `gcc`.
