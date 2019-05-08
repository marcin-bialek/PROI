//  PROI project 2
//  Marcin Białek


#pragma once
#include <string>
#include <Multiset.h>


class TestMultiset {
    void check(bool condition, std::string message);


public:
    void primitiveTypeAppendTest();
    void primitiveTypeRemoveTest();
    void primitiveTypeDoesExistTest();
    void primitiveTypeMultiplicityTest();
    void primitiveTypeSizeTest();
    void primitiveTypeSumTest();
    void primitiveTypeIntersectionTest();
    void primitiveTypeComparisonTest();
    void primitiveTypePrintTest();
    
    void complexTypeAppendTest();
    void complexTypeRemoveTest();
    void complexTypeDoesExistTest();
    void complexTypeMultiplicityTest();
    void complexTypeSizeTest();
    void complexTypeSumTest();
    void complexTypeIntersectionTest();
    void complexTypeComparisonTest();
    void complexTypePrintTest();
};
