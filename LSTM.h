#pragma once

#include "Matrix.h"
#include <string>
#include <vector>
#include <iostream>
#include <cmath>


	class LSTM
	{
	public:
		std::vector<Matrix*> x;
		std::vector<Matrix*>dGates;
		std::vector<Matrix*> w;

		Matrix (*wo),  (*wa),  (*wi),  (*wf), (*doubleu), (*dw), (*b), (*wv);

		Matrix (*u) = new Matrix(1, 4);
		float uo = 0, ua = 0, ui = 0, uf = 0;

		float bo = 0, ba = 0, bi = 0, bf = 0;

		//backward values 
	private:
		std::vector<float> dOut;
		std::vector<float> ObservedOut;


	public:
		class lstm
		{
		public:
			float Out = 0;
			float State = 0;
			float o = 0, a = 0, i = 0, f = 0;

			//for backward phase
			float dState = 0;
		};

	public:
		std::vector<lstm> I = std::vector<lstm>(50);
		int randomGenerator(int seed);
		virtual ~LSTM()
		{
			delete wo;
			delete wa;
			delete wi;
			delete wf;
			delete u;
		}

		void Initialization();
		void SetValues(int t);
		void forward(int t);

		void backward(int t);


		void Run(int t);





		static float Sigmoid(float value);

		static float Tanh(float x);
		static float Tanh2(float x);
	};


