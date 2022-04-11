#include "LSTM.h"
#include "Math.h"
#include <fstream>
#include <string>
using namespace std;




	void LSTM::Initialization()
	{
		I[0].Out = 0;
		I[0].State = 0;
	}

	int LSTM::randomGenerator(int seed)
	{
		return 1;
	}

	void LSTM::SetValues(int t)
	{
		//needs to be changed
		x = std::vector<Matrix*>(t);
		dGates = std::vector<Matrix*>(t);
		ifstream myfile;
		myfile.open("given.txt");
		string line;
		string word;
		int row = 0; 
		int col = 0; 
		vector<Matrix*> arr1 = vector<Matrix*>(100);
		for (int i = 0; i < 100; i++)
		{
			arr1[i] = new Matrix(5, 1);
			x[i] = new Matrix(5, 1);
		}
		if (myfile.is_open())
		{
			while (getline(myfile, line))
			{
				vector<float> x1 = vector<float>();
				cout << line << endl;
				line = line + " ";
				for (int i = 0;i< line.size(); i++)
				{
					if (line[i] == '\t' || line[i] == ' ')
					{
						if (word.size() == 0)
							continue;
						else
						{
							x1.push_back(stof(word));
							col++;
							word = "";
						}
					}
					else
					{
						word = word + line[i];
					}
				}
				arr1[row]->Fill(x1);
				x[row]->Fill(x1);
				row++;
				col = 0;
				for (int i = 0; i < x1.size(); i++)
				{
					cout << x1[i] << "  ";
				}
				cout << endl;
			}
			cout << endl << endl;
		}
		else
		{
			cout << "NOT OPEN"<<endl<<endl;
		}
		myfile.close();

		for (int i = 0; i < arr1.size(); i++)
		{
			arr1[i]->printMatrix();
			cout << endl;
		}
		cout << endl << endl;
		/*for (int i = 0; i < 2; i++)
		{
			x[i] = new Matrix(2, 1);
		
		}*/
		for (int i = 0; i < 100; i++)
		{
			dGates[i] = new Matrix(4, 1);
			cout <<"cho:  "<< &dGates[i] << endl;
		}

		/*std::vector<float> x1 = { 1.0f, 2.0f };
		std::vector<float> x2 = { 0.5f, 3.0f };


		x[0]->Fill(x1);
		x[1]->Fill(x2);*/

		//wehave to replace x with arr1
		std::vector<float> fwa = { 0.45f, 0.25f, 0.5f, 0.5f, 0.5f };
		std::vector<float> fwi = { 0.95f, 0.8f,0.5f, 0.5f, 0.5f };
		std::vector<float> fwf = { 0.7f, 0.45f, 0.5f, 0.5f, 0.5f };
		std::vector<float> fwo = { 0.6f, 0.4f,0.5f, 0.5f, 0.5f };
		std::vector<float> fww = { 0.5f, 0.4f,0.5f, 0.5f, 0.5f };

		std::vector<float> fw = { 0.45f, 0.25f, 0.95f, 0.8f, 0.7f, 0.45f, 0.6f, 0.4f };

		wa = new Matrix(1, 5, fwa);
		wi = new Matrix(1, 5, fwi);
		wf = new Matrix(1, 5, fwf);
		wo = new Matrix(1, 5, fwo);
		wv = new Matrix(1, 5, fww);

		// Matrix of Ws of a,i,f,o
		//make it the last value of input
		w = std::vector<Matrix*>(5);
		
		for (int i = 0; i < 5; i++)
		{
			w[i] = new Matrix(2, 4);
		}
		w[1]->Fill(fw);

		ua = .15f;
		ui = .8f;
		uf = .1f;
		uo = .25f;
		std::vector<float> fu = { ua, ui, uf, uo };
		u->Fill(fu);

		ba = .2f;
		bi = .65f;
		bf = .15f;
		bo = .1f;
		//string a = 1;

		//backwards
		ObservedOut = { .5f, 1.25f };
		dOut = std::vector<float>(t + 1); //needs to demonstrate -1
	}

	void LSTM::forward(int t)
	{
		if (t == 0)
		{
			
			I[t].a = Tanh(Matrix::DotProductValue(wa, (x[t])) + ua * I[t].Out + ba);
			I[t].i = Sigmoid(Matrix::DotProductValue(wi , (x[t])) + ui * I[t].Out + bi);
			I[t].f = Sigmoid(Matrix::DotProductValue(wf,(x[t])) + uf * I[t].Out + bf);
			I[t].o = Sigmoid(Matrix::DotProductValue(wo,(x[t])) + uo * I[t].Out + bo);
			I[t].State = I[t].a * I[t].i + I[t].f * I[t].State;
			I[t].Out = Tanh(I[t].State) * I[t].o;
			Matrix* MOut = new Matrix(1, 1, I[t].Out);
			I[t].Out = Sigmoid(Matrix::DotProductValue(MOut, wv));
		}
		else
		{
			I[t].a = Tanh(Matrix::DotProductValue(wa, (x[t])) + ua * I[t - 1].Out + ba);
			I[t].i = Sigmoid(Matrix::DotProductValue(wi, (x[t])) + ui * I[t - 1].Out + bi);
			I[t].f = Sigmoid(Matrix::DotProductValue(wf, (x[t])) + uf * I[t - 1].Out + bf);
			I[t].o = Sigmoid(Matrix::DotProductValue(wo, (x[t])) + uo * I[t - 1].Out + bo);
			I[t].State = I[t].a * I[t].i + I[t].f * I[t - 1].State;
			I[t].Out = Tanh(I[t].State) * I[t].o;
			Matrix* MOut = new Matrix(1, 1, I[t].Out);
			I[t].Out = Sigmoid(Matrix::DotProductValue(MOut, wv));
		}
		//C# TO C++ CONVERTER TODO TASK: String.Format is not converted to C++ if more than 3 data arguments of different types are specified:
		
		cout<<("Iteration {0}: A {1}, I {2}, F {3}, O {4}, State {5}, Out {6}", t, I[t].a, I[t].i, I[t].f, I[t].o, I[t].State, I[t].Out) << std::endl;
		cout << "Iteration " << t<< ": A: " << I[t].a << ", I: " << I[t].i << ", F: " << I[t].f << ", O: " << I[t].o << ",  State: "<<
			I[t].State << ", Out: " << I[t].Out << endl;
	}

	void LSTM::backward(int t)
	{
		float dt;
		
		std::vector<float> dG(4);

		dt = I[t].Out - ObservedOut[t]; //linear

		if (dOut[t + 1] == 0)
		{
			dOut[t + 1] = dt + dOut[t + 1];
		}

		I[t].dState = dOut[t + 1] * I[t].o * (1 - Tanh2(I[t].State)) + (1 - Tanh2(I[t + 1].dState)) * I[t + 1].f;

		//GATES
		//a
		dG[0] = static_cast<float>(I[t].dState * I[t].i * (1 - std::pow(I[t].a, 2)));
		//i
		dG[1] = I[t].dState * I[t].a * I[t].i * (1 - I[t].i);
		//f
		if (t == 0)
		{
			dG[2] = I[t].dState * I[0].State * I[t].f * (1 - I[t].f);
		}
		else
		{
			dG[2] = I[t].dState * I[t - 1].State * I[t].f * (1 - I[t].f);
		}
		//o
		dG[3] = dOut[t + 1] * Tanh(I[t].State) * I[t].o * (1 - I[t].o);
		dGates[t]->Fill(dG);
		//update w vector
		//updating u vector
		//updating b vector;';;
		//learning rate
		Matrix dx = Matrix::DotProductMatrix(w[t], dGates[t]);
		//  w[t] = Matrix.OuterProduct(dGates,x[t]);

		dOut[t] = Matrix::DotProductValue(u , dGates[t]); //out t-1

		Matrix MDout = Matrix(1, 1, dOut);
		//Updating the W, U, B
		dw = new Matrix(dGates[t]->matrixData.size(), x[t]->matrixData.size());
		*dw = (Matrix::OuterProduct(dGates[t], x[t]));
		if ((t+1) < dGates.size())
		{
			*u = Matrix::OuterProduct(dGates[t + 1], &MDout);
			b = new Matrix(dGates[t + 1]->matrixData.size(), MDout.matrixData.size());
		}
		
		if ((t + 1) < dGates.size())
		{
			*b = Matrix::OuterProduct(dGates[t + 1], &MDout);
		}

		
		cout << "\n\nBackwards " << t << " : dt" << dt << ", dOut: " << dOut[t + 1] << ", F" << I[t].dState << endl;
		//, \nGates : \n{ 4 }dx:\n{ 5 }dOut - 1 {6} ", t, dt, dOut[t + 1], I[t].dState, dGates.ToString(), dx, dOut[t] << std::endl;

		t -= 1;
		for (int i = t; i >= 0; i--)
		{
			if (Matrix::GreaterThan01(*dw) == true)
			{
				backward(i);
			}
		}

 //C# TO C++ CONVERTER TODO TASK: String.Format is not converted to C++ if more than 3 data arguments of different types are specified:
 //C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
		//cout << "\n\nBackwards" << t << ": dt" << dt << ", dOut" << dOut[t + 1] << ", State" << I[t].dState << endl << ", Gates :" << endl;
		//cout << (dGates) << "dx:\n" << dx << " " << dOut[t];

		
		//C# TO C++ CONVERTER TODO TASK: A 'delete dGates' statement was not added since dGates was passed to a method or constructor. Handle memory management manually.
	}

	void LSTM::Run(int t)
	{
		Initialization();
		SetValues(t+1);
		
		double tempT = t;
		int num = 100;
		double TotalRuns = (ceil(tempT / 10));
		cout << "     " << TotalRuns<<"   ";
		for (int i = 0; i < TotalRuns; i++)
		{
			if (t < 100)
			{
				num = t;
			}
			for (int f = 0;  f < num;  f++)
			{
				forward(i);
			}

			//backward(num);
		}


	}

	float LSTM::Sigmoid(float value)
	{
		return 1.0f / (1.0f + static_cast<float>(std::exp(-value)));
	}

	float LSTM::Tanh(float x)
	{
		return static_cast<float>((std::exp(2 * x) - 1) / (std::exp(2 * x) + 1));
	}

	float LSTM::Tanh2(float x)
	{
		return static_cast<float>(std::pow((std::exp(2 * x) - 1) / (std::exp(2 * x) + 1), 2));
	}

