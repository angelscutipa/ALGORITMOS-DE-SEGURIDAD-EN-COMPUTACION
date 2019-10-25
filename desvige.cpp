#include <iostream>
#include <vector>

using namespace std;

string alfa="abcdefghijklmnopqrstuvwxyz";

vector<pair<int,int>> buscar_letras(string input){

	string tri="";
	string comp="";
	vector<pair<int,int>> lista;

	for (int i = 0; i < input.size(); ++i)
	{
		tri+=input[i];
		tri+=input[i+1];
		tri+=input[i+2];
		for (int j = i+1; j < input.size(); ++j)
		{
			comp+=input[j];
			comp+=input[j+1];
			comp+=input[j+2];
			if (tri==comp)
			{
				pair<int, int> tem;
				tem.first=i;
				tem.second=j;
				lista.push_back(tem);
			}
			comp="";
		}
		tri="";
	}

	for (int i = 0; i < lista.size(); ++i)
	{
		//cout<<input[lista[i].first]<<input[lista[i].first + 1]<<input[lista[i].first + 2]<<"  -  "<<input[lista[i].second]<<input[lista[i].second + 1]<<input[lista[i].second + 2]<<endl;
	}

	return lista;

}

vector<int> dis_repetidos(vector<pair<int,int>> input){
	vector<int> sal;
	for (int i = 0; i < input.size(); ++i)
	{
		sal.push_back((input[i].second) - input[i].first);
		cout<<sal[i]<<endl;
	}
	return sal;
}

vector<string> separar(string input, int t_clave){
	vector<string> listas;
	listas.resize(10);
	int tam=input.size()-(input.size()%t_clave);
	for (int i = 0; i < tam; i+=t_clave)
	{
		listas[0]+=input[i];
		listas[1]+=input[i+1];
		listas[2]+=input[i+2];
		listas[3]+=input[i+3];
		listas[4]+=input[i+4];
		listas[5]+=input[i+5];
		listas[6]+=input[i+6];
		listas[7]+=input[i+7];
		listas[8]+=input[i+8];
		listas[9]+=input[i+9];
	}
	for (int i = tam; i < input.size(); ++i)
	{
		listas[i%10]+=input[i];
	}

	for (int i = 0; i < listas.size(); ++i)
	{
		cout<<i<<".-: "<<listas[i]<<endl;
	}

	return listas;
}

class trio
{
public:
	int x=0, y=0, z=0;
	string a,b,c;
	trio(){
		x=0;
		y=0;
		z=0;
	}
	~trio(){};
	
};

void descifrar(vector<string> input){
	vector<int> con_letra;
	con_letra.resize(26);
	for (int i = 0; i < con_letra.size(); ++i){
		con_letra[i]=0;
	}
	vector<trio> mayores;
	for (int i = 0; i < input.size(); ++i){
		for (int j = 0; j < input[i].size(); ++j){
			for (int k = 0; k < alfa.size(); ++k){
				if (input[i][j]==alfa[k]){
					con_letra[k]++;
				}
			}
		}

		trio mejores;
		mejores.x=con_letra[0];
		for (int k = 0; k < con_letra.size(); ++k){
			if (con_letra[k]>mejores.x){
				mejores.x=con_letra[k];
				mejores.a=alfa[k];
			}
		}
		mejores.y=con_letra[0];
		for (int k = 0; k < con_letra.size(); ++k){
			if (con_letra[k]<mejores.x && con_letra[k]>=mejores.y){
				mejores.y=con_letra[k];
				mejores.b=alfa[k];
			}
		}
		mejores.z=con_letra[0];
		for (int k = 0; k < con_letra.size(); ++k){
			if (con_letra[k]<mejores.y && con_letra[k]>=mejores.z){
				mejores.z=con_letra[k];
				mejores.c=alfa[k];
			}
		}
		mayores.push_back(mejores);

		for (int j = 0; j < con_letra.size(); ++j){
			con_letra[j]=0;
		}
	}
	for (int i = 0; i < mayores.size(); ++i){
		cout<<mayores[i].x<<mayores[i].a<<"  "<<mayores[i].y<<mayores[i].b<<"  "<<mayores[i].z<<mayores[i].c<<endl;
	}

}

int main(int argc, char const *argv[])
{
	vector<pair<int,int>> lista;
	string in="dkwvimlyitfeielmkcstiyvzugllstipedtlyzoehkfrkykcsbyyegtaclosfwvrxqwzwqynqlvfiuohhwtzwmsawcqyiemmmaspceyebauncgcwhvxqwzwqynqrlpuxwsearvlruxovyjegxpiiicqomkxlawejuoixnglkcbfnsstlxwshjkcyteimgiupiommjifpskqgkmvifsujyvomgqgwqxmcbbulshoimmxjikwsqzejboomgdbkijmmsxccyaruhnutoqhwwfypuashqhirmmlqohfwvrejyvogiqjzvgyvhtilectzligdbervtqjifptwvdxaombiqimmxjikwsqzecxqwzwqynijmcnmlieuulxymqrtqhklgygibthwtfgeucbprwvitwnzoiqnhvlsjmfphheytacmbseapdbqgwhtipzrkguajtsawytqniejulyvwyyaqgyxmiemnwrdqqrhnchwgtiepcxeuzotbzmrxlkcsekahrxqwzwqynxfwmyahdujqvgmmlsjdimenri";
	lista=buscar_letras(in);

	vector<int> dis;

	dis=dis_repetidos(lista);


	int tam_clave=10;

	vector<string> sub_c;
	sub_c=separar(in, tam_clave);

	descifrar(sub_c);

	return 0;
}