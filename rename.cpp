#include<iostream>

#include<fstream>//文件输入输出流 
#include<cstdio>//rename() 
#include<io.h>

#include<vector>
#include<string>   //strcat:  https://www.runoob.com/cprogramming/c-function-strcat.html


using namespace std;
//不能使用 [] 运算符来访问尚不存在的矢量元素。要将值存储在没有起始大小或已满的矢量中，应使用 push_back 成员函数。该函数接受一个值作为实参，并将其存储在位于矢量末尾的新元素中。


vector<string> allPath;
vector<string> getFilesList(const char * dir)
{

	char dirNew[200];
	strcpy(dirNew, dir);
	strcat(dirNew, "\\*.*");    // 在目录后面加上"\\*.*"进行第一次搜索
 
	intptr_t handle;
	_finddata_t findData;
 
	handle = _findfirst(dirNew, &findData);
	if (handle == -1) {// 检查是否成功
		cout << "can not found the file ... " << endl;
		return allPath;
	}      
 
	do
	{
		if (findData.attrib & _A_SUBDIR)//// 是否含有子目录
		{
			//若该子目录为"."或".."，则进行下一次循环，否则输出子目录名，并进入下一次搜索
			if (strcmp(findData.name, ".") == 0 || strcmp(findData.name, "..") == 0)
				continue;
 
 
			//cout << findData.name << "\t<dir>\n";
			// 在目录后面加上"\\"和搜索到的目录名进行下一次搜索
			strcpy(dirNew, dir);
			strcat(dirNew, "\\");
			strcat(dirNew, findData.name);
			vector<string> tempPath=getFilesList(dirNew);
			allPath.insert(allPath.end(), tempPath.begin(), tempPath.end());
		}
		else //不是子目录，即是文件，则输出文件名和文件的大小
		{
			char *filePath=new char[200];
			strcpy(filePath, dir);
			strcat(filePath, "\\");
			strcat(filePath, findData.name);
			allPath.push_back(filePath);
			//cout << filePath << "\t" << findData.size << " bytes.\n";
			

			
		}
	} while (_findnext(handle, &findData) == 0);
	
	_findclose(handle);    // 关闭搜索句柄
	
	
	return allPath;
}



vector<string> csv_values;

int main(){
	
	
	char dir[200];
	cout << "拖拽进来含要修改名字的文件的文件夹: ";
	cin.getline(dir, 200);	
	
	
	char filename[256];
	cout<<"将csv文件拖拽进来："; 
	cin>>filename;
//	get_excel(filename);//打开csv文件，将信息存入vector动态数组
	
	string FileType = ".";
	cout<<"你要命名的文件格式是"<<endl<<
	"(如：图片格式请输入jpg或png；word格式请输入docx)"<<endl;
	string FType;
	cin>>FType;
	FileType=FileType+FType; 

	ifstream infile(filename);//打开csv文件 
	
	//存入csv文件的数据 
	string value;
	for(int i=0;infile.good();i++){
		
		getline(infile,value,',');
		
		string ndir;
		ndir = dir;
		string file_path = ndir+"\\"+value+FileType;

		
		csv_values.push_back(file_path);
		
//		cout<<csv_values[i]<<endl;//调试用 
	}
		
	 
//
	vector<string> allPath = getFilesList(dir);
	
	cout<<endl; 
	for(int i=0;i<allPath.size();i++){
	
		cout<<"第"<<i+1<<"个要修改的文件是"<<endl<<allPath[i]<<endl;
		
	}
	
	cout<<endl;
	
	for(int i=0;i<csv_values.size();i++){
	
		cout<<"第"<<i+1<<"个可以改成的文件名是"<<endl<<csv_values[i]<<endl;
		
	}	
	
	cout<<"如果你不在乎文件修改是不是不对应的请输入1，否则请输入2"<<endl;
	int choose;
	cin>>choose;

	if(choose == 1){
		for(int i=0;i<allPath.size();i++){
		
			if( rename(allPath[i].c_str(),csv_values[i].c_str()) == 0 ){
				cout<<"第"<<i+1<<"个文件重命名成功"<<endl; 
			}else{
				cout<<"第"<<i+1<<"个文件重命名失败"<<endl; 
			}
			
		}		
	}else{
		
		for(int i=0;i<allPath.size();i++){
	
			cout<<"第"<<i+1<<"个要修改的文件是"<<endl<<allPath[i]<<endl;
			cout<<"请输入你想把它改成第几个名儿，输入数字："; 
		
			int j;
			cin>>j;
			
			if( rename(allPath[i].c_str(),csv_values[j-1].c_str()) == 0 ){
				cout<<"第"<<i+1<<"个文件重命名成功"<<endl; 
			}else{
				cout<<"第"<<i+1<<"个文件重命名失败"<<endl; 
			}
			
			cout<<endl;
		}		
	}

	return 0;
}
