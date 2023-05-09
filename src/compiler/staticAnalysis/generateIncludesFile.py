file = open("nativeIncludes/BraneScript.bs", "w")

file.write("""/* This file was auto generated, please use generateIncludesFile.py
 * to make changes, as the ones here may be overwritten */

export as "BraneScript" 
 {
    struct string{}
 """)

file.write("""
\tbool opr ==(const ref string left, const ref string right) ext;
\tbool opr !=(const ref string left, const ref string right) ext;
\tchar opr [](const ref string source, int index) ext;
\tstring opr +(const ref string left, const ref string right) ext;
""")

file.write("}")