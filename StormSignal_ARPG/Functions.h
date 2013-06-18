#ifndef _FUNCTIONS
#define _FUNCTIONS

//��������(0)�A�����I���(1)
void ScreenTimer(int Type,int FrameRate);

//�L�[�������ꂽ���ǂ������m���߂�
bool CheckKeyDown(int KeyCode);

//������𕪊�����
vector<string> split(string str, string delim);

template <class T> string ntos(T Num)
{
	ostringstream Temp;
	Temp << Num;
	return Temp.str();
}

//A�_��B�_�̋��������߂�
template <class T> double inline GetDistance(T A_X,T A_Y,T B_X,T B_Y)
{
	return hypot(A_X - B_X,A_Y - B_Y);
}

int SetScoreFile(int Score,string Name,string ScoreFileName);

//�X�R�A�t�@�C���̓��e��Ԃ�
vector<string> GetScoreFile(string ScoreFileName);

//�t�@�C�����X�g�̎擾
vector<string> GetFolderList(string folder);

/**
 * �����񒆂��當������������ĕʂ̕�����ɒu������
 * @param str  : �u���Ώۂ̕�����B�㏑����܂��B
 * @param from : ����������
 * @param to   : �u����̕�����
 */
void strReplace (std::string& str, const std::string& from, const std::string& to);

#endif