file = open("nativeIncludes/BraneScript.bs", "w")

file.write("""/* This file was auto generated, please use generateIncludesFile.py
 * to make changes, as the ones here may be overwritten */

export as "BraneScript" 
 {
    struct string{}
    
 """)

scalarTypes = ["uint", "uint64", "int", "int64", "float", "double"]
for t1 in scalarTypes:
    file.write(f"\t// {t1} casts\n")
    for t2 in scalarTypes:
        if t1 == t2:
            continue
        file.write(f"\tconstexpr opr {t1}({t2} arg) ext;\n")
    file.write("\n")
file.write("\t// arithmetic operators\n")
for opr in ["+", "-", "*", "/"]:
    for t1 in scalarTypes:
        file.write(f"\tconstexpr {t1:<6} opr {opr}({t1} left, {t1} right) ext;\n")


file.write("""
\t// logic operators
\tconstexpr bool opr ==(bool left, bool right) ext;
\tconstexpr bool opr !=(bool left, bool right) ext;
\tconstexpr bool opr ==(char left, char right) ext;
\tconstexpr bool opr !=(char left, char right) ext;
""")
for opr in ["==", "!=", "<", "<=", ">", ">="]:
    for t1 in scalarTypes:
        file.write(f"\tconstexpr bool opr {opr}({t1} left, {t1} right) ext;\n")
file.write("""
\tbool opr ==(const ref string left, const ref string right) ext;
\tbool opr !=(const ref string left, const ref string right) ext;
\tchar opr [](const ref string source, int index) ext;
\tstring opr +(const ref string left, const ref string right) ext;
""")

file.write("}")