#include "DxLib.h"
#include "Functions.h"
#include "ConstantValue.h"

void ShowFPS(void)
{//FPS�l�\��
	static int Count = -1;
	static double Show_Count = 0;
	static int Second = 0;
	int Now_Second;

	if(Count < 0)
	{
		Second = GetNowCount();
		Count = 0;
	}

	Count++;

	Now_Second = GetNowCount();
	if(Second + 1000 <= Now_Second)
	{
		Show_Count = Count * 1000. / (Now_Second - Second);
		Second = Now_Second;
		Count = 0;
	}
	DrawFormatString(0,0,Black,"FPS : %f",Show_Count);	
}

//��������(0)�A�����I���(1)
void ScreenTimer(int Type,int FrameRate)
{
	//�^�C�}�[
	static int Timer = 0;
	static double Wait = 0.0;
	//�t���[���X�L�b�v�t���O
	static int FrameSkip = 0;

	if(!Type)
	{
		Timer = GetNowCount();
		ClearDrawScreen();
	}else
	{
		ShowFPS();
		FrameSkip = 0;
		if(!FrameSkip)ScreenFlip() ;
		Wait += (1000.0 / FrameRate - (GetNowCount() - Timer));
		if(Wait > 0)
		{
			Sleep((DWORD)Wait);
			Wait -= (int)Wait;
		}else
		{
			FrameSkip = 1;
		}
	}
}

//�L�[�������ꂽ���ǂ������m���߂�
bool CheckKeyDown(int KeyCode)
{
	static char OldKeyBuf[256];
	char KeyBuf[256];
	if(OldKeyBuf[KeyCode] == 0)
	{
		GetHitKeyStateAll(KeyBuf);
		if(KeyBuf[KeyCode] == 1)
		{
			OldKeyBuf[KeyCode] = 1;
			return true;
		}else
		{
			OldKeyBuf[KeyCode] = 0;
			return false;
		}
	}else
	{
		GetHitKeyStateAll(KeyBuf);
		if(KeyBuf[KeyCode] == 0)
		{
			OldKeyBuf[KeyCode] = 0;
		}
		return false;
	}
}

//������𕶎����Ƃɋ�؂�
vector<string> split(string str, string delim)
{
    vector<string> result;
    int cutAt;
    while( (cutAt = str.find_first_of(delim)) != str.npos )
    {
        if(cutAt > 0)
        {
            result.push_back(str.substr(0, cutAt));
        }
        str = str.substr(cutAt + 1);
    }
    if(str.length() > 0)
    {
        result.push_back(str);
    }
return result;
}

//�t�@�C�����X�g�̎擾
vector<string> GetFolderList(string folder)
{
	// �錾
	vector<string> fileList;
	HANDLE hFind;
	WIN32_FIND_DATA fd;

	// �t�@�C���������̂��߂Ƀ��C���h�J�[�h�ǉ�
	// �� : "D:\\Users\\Pictures\\*.*"
	stringstream ss;
	ss << folder;
	string::iterator itr = folder.end();
	itr--;
	if(*itr != '\\') ss << '\\';
	ss << "*.*";

	// �t�@�C���T��
	// FindFirstFile(�t�@�C����, &fd);
	hFind = FindFirstFile(ss.str().c_str(), &fd);

	// �������s
	if(hFind == INVALID_HANDLE_VALUE){
		std::cout << "�t�@�C���ꗗ���擾�ł��܂���ł���" << std::endl;
		exit(1); // �G���[�I��
	}

	// �t�@�C���������X�g�Ɋi�[���邽�߂̃��[�v
	do{
		// �t�H���_�͏���
		if(!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		  && !(fd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN))
		{
			//�t�@�C���������X�g�Ɋi�[
			char *file = fd.cFileName;
			string str = file;
			fileList.push_back(str);
		}
	}while(FindNextFile(hFind, &fd)); //���̃t�@�C����T��
	
	// hFind�̃N���[�Y
	FindClose(hFind); 

	return fileList;
}

/**
 * �����񒆂��當������������ĕʂ̕�����ɒu������
 * @param str  : �u���Ώۂ̕�����B�㏑����܂��B
 * @param from : ����������
 * @param to   : �u����̕�����
 */
void strReplace (std::string& str, const std::string& from, const std::string& to) {
    std::string::size_type pos = 0;
    while(pos = str.find(from, pos), pos != std::string::npos) {
        str.replace(pos, from.length(), to);
        pos += to.length();
    }
}
