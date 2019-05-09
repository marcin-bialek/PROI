//  PROI project 2
//  Marcin Białek


#include <TestMultiset.h>
#include <iostream>
#include <sstream>
#include <Vector3D.h>



void TestMultiset::check(bool condition, std::string message) {
    if(condition) {
        std::cout << "[" << "\033[32m" << "OK" << "\033[0m" << "] " << message << std::endl;
    }
    else {
        std::cout << "[" << "\033[31m" << "FAIL" << "\033[0m" << "] " << message << std::endl;
        exit(1);
    }
}



void TestMultiset::primitiveTypeAppendTest() {
    Multiset<int> A;
    A.append(1);
    A.append(2, 3);
    A.append(3, 2);
    A.append(1, 2);
    A.append(3);
    
    Multiset<int> expected = {{ 1, 3 }, { 2, 3 }, { 3, 3 }};
    
    check(A == expected, "append() for primitive type");
}



void TestMultiset::primitiveTypeRemoveTest() {
    Multiset<int> A = {{ 1, 3 }, { 2, 3 }, { 3, 3 }};
    A.remove(1);
    A.removeAll(3);
    A.remove(10);
    
    Multiset<int> expected = {{ 1, 2 }, { 2, 3 }};
    
    check(A == expected, "remove() and removeAll() for primitive type");
}



void TestMultiset::primitiveTypeDoesExistTest() {
    Multiset<int> A = {{ 1, 3 }, { 2, 3 }, { 3, 3 }};

    check(A.doesExist(2), "doesExist() for primitive type #1");
    check(!A.doesExist(10), "doesExist() for primitive type #2");
}



void TestMultiset::primitiveTypeMultiplicityTest() {
    Multiset<int> A = {{ 1, 2 }, { 2, 3 }, { 3, 4 }};
    
    check(A.multiplicityOf(1) == 2, "multiplicityOf() for primitive type #1");
    check(A.multiplicityOf(3) == 4, "multiplicityOf() for primitive type #2");
    check(A.multiplicityOf(10) == 0, "multiplicityOf() for primitive type #3");
}



void TestMultiset::primitiveTypeSizeTest() {
    Multiset<int> A = {{ 1, 2 }, { 2, 3 }, { 3, 4 }};
    auto B = A;
     
    B.removeAll(1).removeAll(2).removeAll(3).removeAll(10);

    check(A.length() == 9, "length() for primitive type #1");
    check(B.length() == 0, "length() for primitive type #2");
}



void TestMultiset::primitiveTypeSumTest() {
    Multiset<int> A = {{ 1 }, { 2, 2 }, { 3, 3 }};
    Multiset<int> B = { 1, 2, 3, 4, 5 };
    
    Multiset<int> expected = {{ 1, 2 }, { 2, 3 }, { 3, 4 }, { 4 }, { 5 }};
    
    check(A + B == expected, "sum() for primitive type");
}



void TestMultiset::primitiveTypeIntersectionTest() {
    Multiset<int> A = {{ 1 }, { 2, 3 }, { 3, 3 }};
    Multiset<int> B = { 1, 2, 2, 3, 4, 5 };
    
    Multiset<int> expected = { 1, 2, 2, 3 };

    check(A * B == expected, "intersection() for primitive type");
}



void TestMultiset::primitiveTypeComparisonTest() {
    Multiset<int> A = {{ 1 }, { 2, 3 }, { 3, 3 }};
    Multiset<int> B = {{ 1 }, { 2, 3 }, { 3, 3 }};
    Multiset<int> C = { 1, 2, 3 };
    
    check(A == B, "comparison for primitive type #1");
    check(A != C, "comparison for primitive type #2");
}



void TestMultiset::primitiveTypePrintTest() {
    Multiset<int> A = { 1, 5, 1 };
    std::stringstream ss;
    ss << A;

    std::string expected = "{{ 5, 1 }, { 1, 2 }}";

    check(ss.str() == expected, "printing for primitive type");
}



void TestMultiset::complexTypeAppendTest() {
    Multiset<Vector3D> A;
    A.append({ 1, 2, 3 });
    A.append({ 1, 1, 1 }, 3);
    A.append({ 1, 2, 3 }, 2);
    
    Multiset<Vector3D> expected = {
        {{ 1, 2, 3 }, 3 },
        {{ 1, 1, 1 }, 3 }
    };
    
    check(A == expected, "append() for complex type");
}



void TestMultiset::complexTypeRemoveTest() {
    Multiset<Vector3D> A = {
        {{ 1, 2, 3 }, 3 },
        {{ 1, 1, 1 }, 3 }
    };
    
    A.removeAll({ 1, 2, 3 });
    A.remove({ 1, 1, 1 });
    
    Multiset<Vector3D> expected = {{{ 1, 1, 1 }, 2 }};
    
    check(A == expected, "remove() and removeAll() for complex type");
}



void TestMultiset::complexTypeDoesExistTest() {
    Multiset<Vector3D> A = {
        {{ 1, 2, 3 }, 3 },
        {{ 1, 1, 1 }, 3 }
    };
    
    check(A.doesExist({ 1, 2, 3 }), "doesExist() for complex type #1");
    check(!A.doesExist({ 1, 2, 3.1 }), "doesExist() for complex type #2");
}



void TestMultiset::complexTypeMultiplicityTest() {
    Multiset<Vector3D> A = {
        {{ 1, 2, 3 }, 2 },
        {{ 1, 1, 1 }, 3 }
    };
    
    check(A.multiplicityOf({ 1, 1, 1 }) == 3, "multiplicityOf() for complex type #1"); 
    check(A.multiplicityOf({ 1, 2, 3 }) == 2, "multiplicityOf() for complex type #2");
    check(A.multiplicityOf({ 3, 2, 1 }) == 0, "multiplicityOf() for complex type #3");
}



void TestMultiset::complexTypeSizeTest() {
    Multiset<Vector3D> A = {
        {{ 1, 2, 3 }, 3 },
        {{ 1, 1, 1 }, 3 }
    };
    auto B = A;
    
    B.removeAll({ 1, 2, 3 }).remove({ 1, 1, 1 }).remove({ 1222, 1553, 1745 });
    
    check(A.length() == 6, "length() for complex type #1");
    check(B.length() == 2, "length() for complex type #2");
}



void TestMultiset::complexTypeSumTest() {
    Multiset<Vector3D> A = {{ 1, 2, 3 }, { 1, 2, 3 }, { 10, 10, 10 }};
    Multiset<Vector3D> B = {{ 1, 2, 3 }, { 1234, 1234, 4444 }, { 10, 10, 10 }};
    
    Multiset<Vector3D> expected = {
        {{ 1, 2, 3 }, 3},
        {{ 10, 10, 10 }, 2},
        {{ 1234, 1234, 4444 }}
    };
    
    check(A + B == expected, "sum() for complex type");
}



void TestMultiset::complexTypeIntersectionTest() {
    Multiset<Vector3D> A = {{ 1, 2, 3 }, { 1, 2, 3 }, { 10, 10, 10 }};
    Multiset<Vector3D> B = {{ 1, 2, 3 }, { 1234, 1234, 4444 }, { 10, 10, 10 }, { 10, 10, 10 }};
    
    Multiset<Vector3D> expected = {
        { 1, 2, 3 }, { 10, 10, 10 }
    };
    
    check(A * B == expected, "intersection() for complex type");
}



void TestMultiset::complexTypeComparisonTest() {
    Multiset<Vector3D> A = {{ 1, 2, 3 }, { 1, 2, 3 }, { 10, 10, 10 }};
    Multiset<Vector3D> B;
    B.append({ 1, 2, 3 }, 2).append({ 10, 10, 10 });
    Multiset<Vector3D> C = {{ 1, 2, 3 }, { 1, 2, 3.111 }, { 10, 10, 10 }};
    
    check(A == B, "comparison for complex type #1");
    check(A != C, "comparison for complex type #2");
}



void TestMultiset::complexTypePrintTest() {
    Multiset<Vector3D> A = {{ 1, 2, 3 }, { 5, 5, 5 }};
    std::stringstream ss;
    ss << A;
    
    std::string expected = "{{ [ 5, 5, 5 ], 1 }, { [ 1, 2, 3 ], 1 }}";

    check(ss.str() == expected, "printing for complex type");
}

