#include<iostream>

#include<fstream>//�ļ���������� 
#include<cstdio>//rename() 
#include<io.h>

#include<vector>
#include<string>   //strcat:  https://www.runoob.com/cprogramming/c-function-strcat.html


using namespace std;
//����ʹ�� [] ������������в����ڵ�ʸ��Ԫ�ء�Ҫ��ֵ�洢��û����ʼ��С��������ʸ���У�Ӧʹ�� push_back ��Ա�������ú�������һ��ֵ��Ϊʵ�Σ�������洢��λ��ʸ��ĩβ����Ԫ���С�


vector<string> allPath;
vector<string> getFilesList(const char * dir)
{

	char dirNew[200];
	strcpy(dirNew, dir);
	strcat(dirNew, "\\*.*");    // ��Ŀ¼�������"\\*.*"���е�һ������
 
	intptr_t handle;
	_finddata_t findData;
 
	handle = _findfirst(dirNew, &findData);
	if (handle == -1) {// ����Ƿ�ɹ�
		cout << "can not found the file ... " << endl;
		return allPath;
	}      
 
	do
	{
		if (findData.attrib & _A_SUBDIR)//// �Ƿ�����Ŀ¼
		{
			//������Ŀ¼Ϊ"."��".."���������һ��ѭ�������������Ŀ¼������������һ������
			if (strcmp(findData.name, ".") == 0 || strcmp(findData.name, "..") == 0)
				continue;
 
 
			//cout << findData.name << "\t<dir>\n";
			// ��Ŀ¼�������"\\"����������Ŀ¼��������һ������
			strcpy(dirNew, dir);
			strcat(dirNew, "\\");
			strcat(dirNew, findData.name);
			vector<string> tempPath=getFilesList(dirNew);
			allPath.insert(allPath.end(), tempPath.begin(), tempPath.end());
		}
		else //������Ŀ¼�������ļ���������ļ������ļ��Ĵ�С
		{
			char *filePath=new char[200];
			strcpy(filePath, dir);
			strcat(filePath, "\\");
			strcat(filePath, findData.name);
			allPath.push_back(filePath);
			//cout << filePath << "\t" << findData.size << " bytes.\n";
			

			
		}
	} while (_findnext(handle, &findData) == 0);
	
	_findclose(handle);    // �ر��������
	
	
	return allPath;
}



vector<string> csv_values;

int main(){
	
	
	char dir[200];
	cout << "��ק������Ҫ�޸����ֵ��ļ����ļ���: ";
	cin.getline(dir, 200);	
	
	
	char filename[256];
	cout<<"��csv�ļ���ק������"; 
	cin>>filename;
//	get_excel(filename);//��csv�ļ�������Ϣ����vector��̬����
	
	string FileType = ".";
	cout<<"��Ҫ�������ļ���ʽ��"<<endl<<
	"(�磺ͼƬ��ʽ������jpg��png��word��ʽ������docx)"<<endl;
	string FType;
	cin>>FType;
	FileType=FileType+FType; 

	ifstream infile(filename);//��csv�ļ� 
	
	//����csv�ļ������� 
	string value;
	for(int i=0;infile.good();i++){
		
		getline(infile,value,',');
		
		string ndir;
		ndir = dir;
		string file_path = ndir+"\\"+value+FileType;

		
		csv_values.push_back(file_path);
		
//		cout<<csv_values[i]<<endl;//������ 
	}
		
	 
//
	vector<string> allPath = getFilesList(dir);
	
	cout<<endl; 
	for(int i=0;i<allPath.size();i++){
	
		cout<<"��"<<i+1<<"��Ҫ�޸ĵ��ļ���"<<endl<<allPath[i]<<endl;
		
	}
	
	cout<<endl;
	
	for(int i=0;i<csv_values.size();i++){
	
		cout<<"��"<<i+1<<"�����Ըĳɵ��ļ�����"<<endl<<csv_values[i]<<endl;
		
	}	
	
	cout<<"����㲻�ں��ļ��޸��ǲ��ǲ���Ӧ��������1������������2"<<endl;
	int choose;
	cin>>choose;

	if(choose == 1){
		for(int i=0;i<allPath.size();i++){
		
			if( rename(allPath[i].c_str(),csv_values[i].c_str()) == 0 ){
				cout<<"��"<<i+1<<"���ļ��������ɹ�"<<endl; 
			}else{
				cout<<"��"<<i+1<<"���ļ�������ʧ��"<<endl; 
			}
			
		}		
	}else{
		
		for(int i=0;i<allPath.size();i++){
	
			cout<<"��"<<i+1<<"��Ҫ�޸ĵ��ļ���"<<endl<<allPath[i]<<endl;
			cout<<"��������������ĳɵڼ����������������֣�"; 
		
			int j;
			cin>>j;
			
			if( rename(allPath[i].c_str(),csv_values[j-1].c_str()) == 0 ){
				cout<<"��"<<i+1<<"���ļ��������ɹ�"<<endl; 
			}else{
				cout<<"��"<<i+1<<"���ļ�������ʧ��"<<endl; 
			}
			
			cout<<endl;
		}		
	}

	return 0;
}
