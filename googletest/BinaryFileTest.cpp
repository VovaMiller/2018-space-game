#include <gtest/gtest.h>
#include <DiggerOffline/BinaryFile.h>
#include <fstream>
#include <limits>


class BinaryFileTest : public ::testing::Test {
public:
    BinaryFileTest() {
        std::ofstream ofs(kFileName, std::ios_base::out | std::ios_base::trunc);
    }
    ~BinaryFileTest() {
        std::remove(kFileName.c_str());
    }
    static const std::string kFileName;
};

const std::string BinaryFileTest::kFileName = "BinaryFileTest";


TEST_F(BinaryFileTest, Int) {
    int a0 = 0;
    int b0 = 123456789;
    int c0 = -123456789;
    int d0 = std::numeric_limits<int>::min();
    int e0 = std::numeric_limits<int>::max();
    std::ofstream ofs(BinaryFileTest::kFileName);
    BinaryFile::WriteInt(ofs, a0);
    BinaryFile::WriteInt(ofs, b0);
    BinaryFile::WriteInt(ofs, c0);
    BinaryFile::WriteInt(ofs, d0);
    BinaryFile::WriteInt(ofs, e0);
    ofs.close();
    
    std::ifstream ifs(BinaryFileTest::kFileName);
    int a1 = BinaryFile::ReadInt(ifs);
    int b1 = BinaryFile::ReadInt(ifs);
    int c1 = BinaryFile::ReadInt(ifs);
    int d1 = BinaryFile::ReadInt(ifs);
    int e1 = BinaryFile::ReadInt(ifs);
    ifs.close();
    
    ASSERT_EQ(a0, a1);
    ASSERT_EQ(b0, b1);
    ASSERT_EQ(c0, c1);
    ASSERT_EQ(d0, d1);
    ASSERT_EQ(e0, e1);
}

TEST_F(BinaryFileTest, LongLong) {
    long long a0 = 0;
    long long b0 = 123456789;
    long long c0 = -123456789;
    long long d0 = std::numeric_limits<long long>::min();
    long long e0 = std::numeric_limits<long long>::max();
    std::ofstream ofs(BinaryFileTest::kFileName);
    BinaryFile::WriteLongLong(ofs, a0);
    BinaryFile::WriteLongLong(ofs, b0);
    BinaryFile::WriteLongLong(ofs, c0);
    BinaryFile::WriteLongLong(ofs, d0);
    BinaryFile::WriteLongLong(ofs, e0);
    ofs.close();
    
    std::ifstream ifs(BinaryFileTest::kFileName);
    long long a1 = BinaryFile::ReadLongLong(ifs);
    long long b1 = BinaryFile::ReadLongLong(ifs);
    long long c1 = BinaryFile::ReadLongLong(ifs);
    long long d1 = BinaryFile::ReadLongLong(ifs);
    long long e1 = BinaryFile::ReadLongLong(ifs);
    ifs.close();
    
    ASSERT_EQ(a0, a1);
    ASSERT_EQ(b0, b1);
    ASSERT_EQ(c0, c1);
    ASSERT_EQ(d0, d1);
    ASSERT_EQ(e0, e1);
}

TEST_F(BinaryFileTest, Double) {
    double a0 = 0.0;
    double b0 = 3.14159;
    double c0 = -3.14159;
    double d0 = std::numeric_limits<double>::lowest();
    double e0 = std::numeric_limits<double>::min();
    double f0 = std::numeric_limits<double>::max();
    std::ofstream ofs(BinaryFileTest::kFileName);
    BinaryFile::WriteDouble(ofs, a0);
    BinaryFile::WriteDouble(ofs, b0);
    BinaryFile::WriteDouble(ofs, c0);
    BinaryFile::WriteDouble(ofs, d0);
    BinaryFile::WriteDouble(ofs, e0);
    BinaryFile::WriteDouble(ofs, f0);
    ofs.close();
    
    std::ifstream ifs(BinaryFileTest::kFileName);
    double a1 = BinaryFile::ReadDouble(ifs);
    double b1 = BinaryFile::ReadDouble(ifs);
    double c1 = BinaryFile::ReadDouble(ifs);
    double d1 = BinaryFile::ReadDouble(ifs);
    double e1 = BinaryFile::ReadDouble(ifs);
    double f1 = BinaryFile::ReadDouble(ifs);
    ifs.close();
    
    ASSERT_DOUBLE_EQ(a0, a1);
    ASSERT_DOUBLE_EQ(b0, b1);
    ASSERT_DOUBLE_EQ(c0, c1);
    ASSERT_EQ(d0, d1);
    ASSERT_EQ(e0, e1);
    ASSERT_EQ(f0, f1);
}


TEST_F(BinaryFileTest, String) {
    std::string a0 = "";
    std::string b0 = "0";
    std::string c0 = "a";
    std::string d0 = "Hello world!";
    std::string e0 = "Don't fail.\nPlease!";
    std::ofstream ofs(BinaryFileTest::kFileName);
    BinaryFile::WriteString(ofs, a0);
    BinaryFile::WriteString(ofs, b0);
    BinaryFile::WriteString(ofs, c0);
    BinaryFile::WriteString(ofs, d0);
    BinaryFile::WriteString(ofs, e0);
    ofs.close();
    
    std::ifstream ifs(BinaryFileTest::kFileName);
    std::string a1 = BinaryFile::ReadString(ifs);
    std::string b1 = BinaryFile::ReadString(ifs);
    std::string c1 = BinaryFile::ReadString(ifs);
    std::string d1 = BinaryFile::ReadString(ifs);
    std::string e1 = BinaryFile::ReadString(ifs);
    ifs.close();
    
    ASSERT_EQ(a0, a1);
    ASSERT_EQ(b0, b1);
    ASSERT_EQ(c0, c1);
    ASSERT_EQ(d0, d1);
    ASSERT_EQ(e0, e1);
}

TEST_F(BinaryFileTest, Bool) {
    bool a0 = true;
    bool b0 = false;
    bool c0 = false;
    bool d0 = true;
    bool e0 = true;
    std::ofstream ofs(BinaryFileTest::kFileName);
    BinaryFile::WriteBool(ofs, a0);
    BinaryFile::WriteBool(ofs, b0);
    BinaryFile::WriteBool(ofs, c0);
    BinaryFile::WriteBool(ofs, d0);
    BinaryFile::WriteBool(ofs, e0);
    ofs.close();
    
    std::ifstream ifs(BinaryFileTest::kFileName);
    bool a1 = BinaryFile::ReadBool(ifs);
    bool b1 = BinaryFile::ReadBool(ifs);
    bool c1 = BinaryFile::ReadBool(ifs);
    bool d1 = BinaryFile::ReadBool(ifs);
    bool e1 = BinaryFile::ReadBool(ifs);
    ifs.close();
    
    ASSERT_EQ(a0, a1);
    ASSERT_EQ(b0, b1);
    ASSERT_EQ(c0, c1);
    ASSERT_EQ(d0, d1);
    ASSERT_EQ(e0, e1);
}
