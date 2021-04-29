#include <iostream>
#include <cmath>
#include <gtest/gtest.h>
#include "../include/student.hpp"
#include "../include/math.hpp"

TEST(StudentClassTest, ClassCreateUsingName){
    Student student("Vardenis", "Pavardenis");
    EXPECT_EQ("Vardenis", student.getFirstName());
    EXPECT_EQ("Pavardenis", student.getLastName());
    EXPECT_EQ(0, student.getGradeCount());
    EXPECT_EQ(0, student.getExamGrade());
    EXPECT_EQ(0, student.getFinalMeanGrade());
    EXPECT_EQ(0, student.getFinalMedianGrade());
}

TEST(StudentClassTest, ClassCopyConstructor){
    Student student("Vardenis", "Pavardenis");
    student.setExamGrade(9);
    student.addGrade(1);
    student.addGrade(2);
    student.addGrade(3);
    student.addGrade(4);
    student.addGrade(5);
    student.processGrades();
    Student newStudent(student);
    EXPECT_EQ("Vardenis", student.getFirstName());
    EXPECT_EQ("Pavardenis", student.getLastName());
    EXPECT_EQ(5, student.getGradeCount());
    EXPECT_EQ(9, student.getExamGrade());
    EXPECT_EQ(6.6, student.getFinalMeanGrade());
    EXPECT_EQ(6.6, student.getFinalMedianGrade());
    EXPECT_EQ("Vardenis", newStudent.getFirstName());
    EXPECT_EQ("Pavardenis", newStudent.getLastName());
    EXPECT_EQ(5, newStudent.getGradeCount());
    EXPECT_EQ(9, newStudent.getExamGrade());
    EXPECT_EQ(6.6, newStudent.getFinalMeanGrade());
    EXPECT_EQ(6.6, newStudent.getFinalMedianGrade());
}

TEST(StudentClassTest, ClassMoveConstructor){
    Student student("Vardenis", "Pavardenis");
    student.setExamGrade(9);
    student.addGrade(1);
    student.addGrade(2);
    student.addGrade(3);
    student.addGrade(4);
    student.addGrade(5);
    student.processGrades();
    Student newStudent(std::move(student));
    EXPECT_EQ("", student.getFirstName());
    EXPECT_EQ("", student.getLastName());
    EXPECT_EQ(0, student.getGradeCount());
    EXPECT_EQ(0, student.getExamGrade());
    EXPECT_EQ(0, student.getFinalMeanGrade());
    EXPECT_EQ(0, student.getFinalMedianGrade());
    EXPECT_EQ("Vardenis", newStudent.getFirstName());
    EXPECT_EQ("Pavardenis", newStudent.getLastName());
    EXPECT_EQ(5, newStudent.getGradeCount());
    EXPECT_EQ(9, newStudent.getExamGrade());
    EXPECT_EQ(6.6, newStudent.getFinalMeanGrade());
    EXPECT_EQ(6.6, newStudent.getFinalMedianGrade());
}

TEST(StudentClassTest, ClassCopyOperator){
    Student student("Vardenis", "Pavardenis");
    student.setExamGrade(9);
    student.addGrade(1);
    student.addGrade(2);
    student.addGrade(3);
    student.addGrade(4);
    student.addGrade(5);
    student.processGrades();
    Student newStudent = student;
    EXPECT_EQ("Vardenis", student.getFirstName());
    EXPECT_EQ("Pavardenis", student.getLastName());
    EXPECT_EQ(5, student.getGradeCount());
    EXPECT_EQ(9, student.getExamGrade());
    EXPECT_EQ(6.6, student.getFinalMeanGrade());
    EXPECT_EQ(6.6, student.getFinalMedianGrade());
    EXPECT_EQ("Vardenis", newStudent.getFirstName());
    EXPECT_EQ("Pavardenis", newStudent.getLastName());
    EXPECT_EQ(5, newStudent.getGradeCount());
    EXPECT_EQ(9, newStudent.getExamGrade());
    EXPECT_EQ(6.6, newStudent.getFinalMeanGrade());
    EXPECT_EQ(6.6, newStudent.getFinalMedianGrade());
}

TEST(StudentClassTest, ClassMoveOperator){
    Student student("Vardenis", "Pavardenis");
    student.setExamGrade(9);
    student.addGrade(1);
    student.addGrade(2);
    student.addGrade(3);
    student.addGrade(4);
    student.addGrade(5);
    student.processGrades();
    Student newStudent = std::move(student);
    EXPECT_EQ("", student.getFirstName());
    EXPECT_EQ("", student.getLastName());
    EXPECT_EQ(0, student.getGradeCount());
    EXPECT_EQ(0, student.getExamGrade());
    EXPECT_EQ(0, student.getFinalMeanGrade());
    EXPECT_EQ(0, student.getFinalMedianGrade());
    EXPECT_EQ("Vardenis", newStudent.getFirstName());
    EXPECT_EQ("Pavardenis", newStudent.getLastName());
    EXPECT_EQ(5, newStudent.getGradeCount());
    EXPECT_EQ(9, newStudent.getExamGrade());
    EXPECT_EQ(6.6, newStudent.getFinalMeanGrade());
    EXPECT_EQ(6.6, newStudent.getFinalMedianGrade());
}

TEST(Math, FindMean) {
    vector<int> container = {2,8,10,6,7,4,5,1,9,3};
    EXPECT_EQ(5.5, round(findMean(container) * 100)/100.0);
}

TEST(Math, FindMedian) {
    vector<int> container = {2,8,10,6,7};
    EXPECT_EQ(7.0, round(findMedian(container) * 100)/100.0);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}