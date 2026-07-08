#!/usr/bin/env python3
import sys
import re
def bad(msg, line, file):
    print(f"{file}:{line}: BAD: {msg}")
    sys.exit(1)
ban = bad
def check_file(path):
    try:
        f = open(path, "r", encoding="utf-8", errors="replace")
    except Exception as e:
        print(f"{path}: cannot open: {e}")
        return
    last_blank = False
    for line_num, line in enumerate(f, start=1):
        stripped = line.rstrip("\n")
        if len(stripped) > 80:
            ban("line too long (>80)", line_num, path)
        if "\t" in line:
            ban("TAB detected", line_num, path)
        if stripped != line.rstrip():
            ban("trailing spaces", line_num, path)
        blank = (stripped == "")
        if blank and last_blank:
            ban("double empty line", line_num, path)
        last_blank = blank
        m = re.search(r"\b([A-Za-z_][A-Za-z0-9_]*)\s+\*([A-Za-z_])", line)
        if m:
            if not re.search(r"\(\s*[A-Za-z_][A-Za-z0-9_]*\s*\*\s*\)", line):
                ban("bad pointer style (use TYPE* name)", line_num, path)
        if "if(" in line:
            ban("if( without space", line_num, path)
        if stripped.startswith("#if") and not stripped.startswith("#if "):
            ban("bad #if style", line_num, path)
        m = re.match(r"^\s*static\s+(?:inline\s+)?[A-Za-z_][A-Za-z0-9_]*\s+([A-Za-z_][A-Za-z0-9_]*)\s*\(", stripped)
        if m:
            fname = m.group(1)
            if not fname.startswith("__"):
                ban("static function must start with __", line_num, path)
    f.close()
def main():
    if len(sys.argv) < 2:
        print("usage: stylecheck.py <file1> [file2...]")
        return
    for path in sys.argv [1:]:
        check_file(path)
    print("OK: style clean")
if __name__ == "__main__":
    main()
