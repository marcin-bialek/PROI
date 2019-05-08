//  PROI project 2
//  Marcin Białek


#include <TestMultiset.h>


int main() {
    TestMultiset test;

    test.primitiveTypeAppendTest();
    test.primitiveTypeRemoveTest();
    test.primitiveTypeDoesExistTest();
    test.primitiveTypeMultiplicityTest();
    test.primitiveTypeSizeTest();
    test.primitiveTypeSumTest();
    test.primitiveTypeIntersectionTest();
    test.primitiveTypeComparisonTest();
    test.primitiveTypePrintTest();

    test.complexTypeAppendTest();
    test.complexTypeRemoveTest();
    test.complexTypeDoesExistTest();
    test.complexTypeMultiplicityTest();
    test.complexTypeSizeTest();
    test.complexTypeSumTest();
    test.complexTypeIntersectionTest();
    test.complexTypeComparisonTest();
    test.complexTypePrintTest();
}

