程式部分:
	使用C++
	cpp檔案僅 main.cpp
	因為程式內部預設開啟的inputfile為 Prog1_note/input.txt
	故需要保存Prog1_note此資料夾
	其他outputfile和main.cpp在同一目錄下





編譯執行部分:
	編譯main.cpp並執行即可




演算法部分:
  1.此次利用到stringstream這個函示庫
    用來把一串陣列轉換成string 或反之 例如1 3 4 6 7 先把它存成string 再把它存進矩陣
    stringstream ss;
    string string;
    int number;
    ss>>string; 代表把string內容寫入stringstream當中
    ss<<number; 代表把stringstream東西輸入給number
    https://dexter7311.pixnet.net/blog/post/25285835
  2.利用depth 紀錄depth i有哪些vertex
	ranking 紀錄index i的vertex的ranking
	 value紀錄index i的vertex的value 等概念
  3.這個程式為BST 和 splay tree實做