#include "testing.h"
/*
#include "../src/functionHandle.h"

using namespace BraneScript;

TEST(BraneScript, FuncDefTests)
{
    FuncDef empty("empty()");
    EXPECT_TRUE(empty.sig() == "empty") << empty.sig();
    EXPECT_EQ(empty.argCount(), 0);

    FuncDef structMember("struct::member()");
    EXPECT_TRUE(structMember.sig() == "struct::member") << structMember.sig();
    EXPECT_EQ(structMember.argCount(), 1);
    EXPECT_TRUE(structMember.argType(0) == "struct") << structMember.argType(0);
    EXPECT_FALSE(structMember.argIsConst(0));
    EXPECT_TRUE(structMember.argIsRef(0));

    FuncDef simple("simple(int)");
    EXPECT_TRUE(simple.sig() == "simple") << simple.sig();
    EXPECT_EQ(simple.argCount(), 1);
    EXPECT_TRUE(simple.argType(0) == "int") << simple.argType(0);
    EXPECT_FALSE(simple.argIsConst(0));
    EXPECT_FALSE(simple.argIsRef(0));

    FuncDef simple2("simple(int,float)");
    EXPECT_TRUE(simple2.sig() == "simple") << simple2.sig();
    EXPECT_EQ(simple2.argCount(), 2);
    EXPECT_TRUE(simple2.argType(0) == "int") << simple2.argType(0);
    EXPECT_FALSE(simple2.argIsConst(0));
    EXPECT_FALSE(simple2.argIsRef(0));
    EXPECT_TRUE(simple2.argType(1) == "float") << simple2.argType(1);
    EXPECT_FALSE(simple2.argIsConst(1));
    EXPECT_FALSE(simple2.argIsRef(1));


    FuncDef complex("complex(const int,ref float,const ref StructType,int)");
    EXPECT_TRUE(complex.sig() == "complex") << complex.sig();
    EXPECT_EQ(complex.argCount(), 4);
    EXPECT_TRUE(complex.argType(0) == "int") << complex.argType(0);
    EXPECT_TRUE(complex.argIsConst(0));
    EXPECT_FALSE(complex.argIsRef(0));
    EXPECT_TRUE(complex.argType(1) == "float") << complex.argType(1);
    EXPECT_FALSE(complex.argIsConst(1));
    EXPECT_TRUE(complex.argIsRef(1));
    EXPECT_TRUE(complex.argType(2) == "StructType") << complex.argType(2);
    EXPECT_TRUE(complex.argIsConst(2));
    EXPECT_TRUE(complex.argIsRef(2));
    EXPECT_TRUE(complex.argType(3) == "int") << complex.argType(3);
    EXPECT_FALSE(complex.argIsConst(3));
    EXPECT_FALSE(complex.argIsRef(3));
}*/
