# -Wall -Wextra  => 显示编译过程中的所有警告和错误信息
# -o  => 指定编译后的文件名，后缀自动
# -finput-charset=utf-8  => 指定源代码文件是使用UTF-8编码。这告诉编译器在读取和编译这个文件时应该如何解释其中的字符。
# -fexec-charset=GBK  => 指定在程序运行时，字符串字面量和某些其他字符数据（例如，通过std::cout输出的）应该使用GBK编码。
g++ -Wall -Wextra .\main.cpp -o main -finput-charset=utf-8 -fexec-charset=GBK


# 设置 PowerShell 输出编码为 UTF-8
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8

# 设置 PowerShell 输入编码为 UTF-8
[Console]::InputEncoding = [System.Text.Encoding]::UTF8