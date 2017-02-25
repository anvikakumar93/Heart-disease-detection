//
//  main.cpp
//  CSE537
//
//  Created by Yulingfei Li on 11/10/15.
//  Copyright © 2015 Yulingfei Li. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>

using namespace std;

const int dataNum = 297;
int m = 296;
float weight0 = 1;
float weight1 = 1.2;
int K = 20;
float n = 0.5;

float* set[dataNum];
struct Rule{
    float term[13];
    int C;
    float CF;
};
vector<Rule> rules;

bool Input(string name)
{
    if(name == "")
        name = "/Users/Yulingfei/Downloads/1.txt";
    FILE *f = fopen(name.c_str(), "r");
    if(!f)
        return false;
    float *b;
    int index=0;
    float max[13], min[13];
    while(index != dataNum){
        b = new float[14];
        fscanf(f, "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f", &b[0], &b[1], &b[2], &b[3], &b[4], &b[5], &b[6], &b[7], &b[8], &b[9], &b[10], &b[11], &b[12], &b[13]);
        for(int i = 0; i != 13; ++i){
            if(index == 0)
                max[i] = min[i] = b[i];
            else{
                if(b[i] > max[i])
                    max[i] = b[i];
                if(b[i] < min[i])
                    min[i] = b[i];
            }
        }
        set[index++] = b;
    }
    fclose(f);
    //normalize
    for(int i = 0; i != dataNum; ++i){
        for(int j = 0; j != 13; ++j)
            set[i][j] = (set[i][j]-min[j])/(max[j] - min[j]);
        if(set[i][13] > 0)
            set[i][13] = 1;
    }
    return true;
}

void GenerateFussyRule(int n, float term[13])
{
    if(n > 0){
        term[13-n] = 0;
        GenerateFussyRule(n - 1, term);
        term[13-n] = 0.5;
        GenerateFussyRule(n - 1, term);
        term[13-n] = 1;
        GenerateFussyRule(n - 1, term);
    }
    else{
        float betaClass0 = 0, betaClass1 = 0;
        for(int i = 0; i != m; ++i){
            //muX = mux0*mux1*...*mux12
            float Mux = 1;
            for(int j = 0; j != 13; ++j){
                if(term[j] == 0){
                    float v = -2*set[i][j] + 1;
                    if(v > 0)
                        Mux *= v;
                    else{
                        Mux = 0;
                        break;
                    }
                }
                else if(term[j] == 0.5){
                    float v = 2*(set[i][j] - 0.5);
                    if(v < 0){
                        Mux *= 1 + v;
                    }
                    else{
                        Mux *= 1 - v;
                    }
                }else{
                    float v =  2*set[i][j] - 1;
                    if(v > 0)
                        Mux *= v;
                    else{
                        Mux = 0;
                        break;
                    }
                }
            }
            if(set[i][13] > 0){//class 1
                betaClass1 += Mux;
            }
            else{// class 0
                betaClass0 += Mux;
            }
        }
        betaClass0 *= weight0;
        betaClass1 *= weight1;
        Rule result;
        if(betaClass0 > betaClass1){
            result.C = 0;
            result.CF = (betaClass0 - betaClass1)/(betaClass0 + betaClass1);
        }
        else if(betaClass0 < betaClass1){
            result.C = 1;
            result.CF = (betaClass1 - betaClass0)/(betaClass0 + betaClass1);
        }
        else//This rule is useless
            return;
        for(int i = 0; i != 13; ++i)
            result.term[i] = term[i];
        rules.push_back(result);
    }
}

void Train()
{
    for(int k = 0; k != K; ++k){
        vector<Rule>::iterator keep0, keep1;
        int c = 0;
        for(int p = 0; p != m; ++p){
            float alphaClass0 = 0, alphaClass1 = 0;
            for(vector<Rule>::iterator iter = rules.begin(); iter != rules.end(); ++iter){
                //muX = mux0*mux1*...*mux12
                float Mux = 1;
                for(int j = 0; j != 13; ++j){
                    if(iter -> term[j] == 0){
                        float v = -2*set[p][j] + 1;
                        if(v > 0)
                            Mux *= v;
                        else{
                            Mux = 0;
                            break;
                        }
                    }
                    else if(iter->term[j] == 0.5){
                        float v = 2*(set[p][j] - 0.5);
                        if(v < 0){
                            Mux *= 1 + v;
                        }
                        else{
                            Mux *= 1 - v;
                        }
                    }else{
                        float v =  2*set[p][j] - 1;
                        if(v > 0)
                            Mux *= v;
                        else{
                            Mux = 0;
                            break;
                        }
                    }
                }
                if(iter->C != 0){
                    if(Mux*iter->CF > alphaClass1){
                        alphaClass1 = Mux*iter->CF;
                        keep1 = iter;
                    }
                }
                else{
                    if(Mux*iter->CF > alphaClass0){
                        alphaClass0 = Mux*iter->CF;
                        keep0 = iter;
                    }
                }
            }
            if(alphaClass0 < alphaClass1)
                c = 1;
            else if(alphaClass0 > alphaClass1)
                c = 0;
            else
                c = -1;
            if(c >= 0 && c != set[p][13]){
                if(c > 0){
                    keep1->CF = keep1->CF - keep1->CF*n*weight0;
                    keep0->CF = keep0->CF + n*weight0*(1 - keep0->CF);//*the original equation 12 may be wrong
                }
                else{
                    keep0->CF = keep0->CF - keep0->CF*n*weight1;
                    keep1->CF = keep1->CF + n*weight1*(1 - keep1->CF);//*the original equation 12 may be wrong
                }
            }
        }
    }
}

int Test(int mm)
{
    float alphaClass0 = 0, alphaClass1 = 0;
    for(vector<Rule>::iterator iter = rules.begin(); iter != rules.end(); ++iter){
        //muX = mux0*mux1*...*mux12
        float Mux = 1;
        for(int j = 0; j != 13; ++j){
            if(iter -> term[j] == 0){
                float v = -2*set[mm][j] + 1;
                if(v > 0)
                    Mux *= v;
                else
                    Mux = 0;
            }
            else if(iter->term[j] == 0.5){
                float v = 2*(set[mm][j] - 0.5);
                if(v < 0){
                    Mux *= 1 + v;
                }
                else{
                    Mux *= 1 - v;
                }
            }else{
                float v =  2*set[mm][j] - 1;
                if(v > 0)
                    Mux *= v;
                else
                    Mux = 0;
            }
        }
        if(iter->C != 0){
            if(Mux*iter->CF > alphaClass1){
                alphaClass1 = Mux*iter->CF;
            }
        }
        else{
            if(Mux*iter->CF > alphaClass0){
                alphaClass0 = Mux*iter->CF;
            }
        }
    }
    int rr;
    if(alphaClass0 < alphaClass1)
        rr = 1; 
    else if(alphaClass0 > alphaClass1)
        rr = 0; 
    else
        rr = -1;
    cout << rr << ' ';
    if(rr == set[mm][13]){
        //cout << 1 << endl;
		return 1;
	}
    else{
        //cout << 0 << endl;
		return 0;
	}
}

void Export(){
    FILE *f = fopen("rule.txt", "w");
    for(vector<Rule>::iterator i = rules.begin(); i != rules.end(); ++i){
        fprintf(f, "%f %f %f %f %f %f %f %f %f %f %f %f %f %d %f\n", i->term[0], i->term[1], i->term[2], i->term[3], i->term[4], i->term[5], i->term[6], i->term[7], i->term[8], i->term[9], i->term[10], i->term[11], i->term[12], i->C, i->CF);
    }
    fclose(f);
}

void Import(){
    FILE *f = fopen("rule.txt", "r");
    Rule *i = new Rule;
    while(!feof(f)){
        fscanf(f, "%f %f %f %f %f %f %f %f %f %f %f %f %f %d %f\n", &i->term[0], &i->term[1], &i->term[2], &i->term[3], &i->term[4], &i->term[5], &i->term[6], &i->term[7], &i->term[8], &i->term[9], &i->term[10], &i->term[11], &i->term[12], &i->C, &i->CF);
        rules.push_back(*i);
    }
    delete i;
    fclose(f);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    string name = "";
    int mm = 296;
    int mode = 0;
    if(argc == 9){
        name = argv[1];
        mode = atoi(argv[2]);
        weight0 = (float)atof(argv[3]);
        weight1 = (float)atof(argv[4]);
        m = (float)atof(argv[5]);
        K = atoi(argv[6]);
        n = (float)atof(argv[7]);
        mm = atoi(argv[8]);
    }
    else if(argc == 4){
		int count = 0;
	    name = argv[1];
		if(!Input(name))
			return 1;
		Import();
	    int begin = atoi(argv[2]);
	    int end = atoi(argv[3]);
	    for(int i = begin; i != end; ++i){
			count += Test(i);
		}
		printf("%.1lf\n", 100.0*count/(end - begin + 1));
		return 0;
	}
	else if(argc == 2){
        Import();
		name = argv[1];
		float *bb = new float[13];
		FILE *ffo = fopen(name.c_str(), "r");
		for(int ii = 0; ii != 13; ++ii){
			fscanf(ffo, "%f", bb + ii);
		}
		fclose(ffo);
		set[1] = bb;
		Test(1);
		return 0;
	}

    if(!Input(name))
        return 1;
    float term[13];
    if(mode == 0){
        GenerateFussyRule(13, term);
        Train();
        Test(mm);
    }
    else if(mode == 1){
        GenerateFussyRule(13, term);
        Export();
    }
    else if(mode == 2){
        GenerateFussyRule(13, term);
        Train();
        Export();
    }
    else if(mode == 3){
        Import();
        Train();
        Test(mm);
    }
    else{
        Import();
        Test(mm);
    }
    return 0;
}
