#include<bits/stdc++.h>
#define vi vector<int>
#define vl vector<ll>
#define ll long long
using namespace std;

class BFUs{
	private:
		int radix;
		int spacing;
		vector<queue<int>> ques;
		int output;
		bool recieve_input;
		int counter;
		int N;

		void print_que(queue<int> &q){
			queue<int> copy_q = q;
			for(int i = 0 ; i < spacing ; i++){
				if(copy_q.empty()){
					cout << "-";
				} else {
					cout << copy_q.front();
					copy_q.pop();
				}
				cout << " ";
			}
			cout << "\n";
		}

	public:
		int check_out(){
			return output;
		}

		void set_input(bool inp){
			recieve_input = inp;
		}
		
		void take_in(int x){
			if(recieve_input){
				if(((counter/spacing)%radix) == radix - 1){
					output = counter - (spacing * (radix - 1));

					int copy_output = output + spacing;
					for(queue<int> &q : ques){ 
						q.pop();
						q.push(-copy_output);
						copy_output += spacing;
					}
				}
				else{
					if(true){
						if(x < N){
							ques[(counter/spacing)%radix].push(x);
						}
						if(!ques[(counter/spacing)%radix].empty() && (ques[(counter/spacing)%radix].front() < 0)){
							ques[(counter/spacing)%radix].pop();
						}
					}
					output = max(-1 , counter - (spacing * (radix - 1)));
				}
				if(output >= N){output = -1;}
				counter++;
			}
		}

		void view_bfu(int input){
			cout << "--------------------------------------------------------------------\n";
			cout << "input = " << input << "\n";
			for(queue<int> &q : ques){
				print_que(q);
			}
			cout << "output = " << output << "\n";
			cout << "--------------------------------------------------------------------\n";
		}

		BFUs(int a_spacing = 64 , int a_radix = 8, int a_N = 512) : spacing(a_spacing) , radix(a_radix) , output(-1) , 
					recieve_input(false) , counter(0) , ques(vector<queue<int>>(a_radix - 1)) , N(a_N) {}
};

int main(){
	int radix = 4 , N = 64, logn = 3;; 
	int intial_spacing = N/radix;
	freopen("output.txt" , "w" , stdout);
	
	vector<BFUs> bfus(logn + 1);
	for(int i = 0 ;i < logn ; i++){
		bfus[i] = BFUs(intial_spacing , radix , N);
		intial_spacing /= radix;
	}
	bfus[0].set_input(true);
	for(int i = 0 ; i < 2*N ; i++){
		int x = i;

		vi inputs;

		for(int curr_stage = 0 ; curr_stage < logn ; curr_stage++){
			inputs.push_back(x);
			bfus[curr_stage].take_in(x);
			x = bfus[curr_stage].check_out();
			if(x >= 0){
				bfus[curr_stage + 1].set_input(true);
			}
		}
		cout << "///////////////////////////clock cycle = " << i << "/////////////////////////////////\n";
		int counter = 0;
		for(int curr_stage = 0 ; curr_stage < logn ; curr_stage++){
			// cout << "input = " << inputs[counter++] << "\n";
			bfus[curr_stage].view_bfu(inputs[counter++]);
		}
		// if(i < 3*N/4){
		// 	this_thread::sleep_for(chrono::milliseconds(500));
		// } else {
		// 	this_thread::sleep_for(chrono::milliseconds(2000));
		// }
		// this_thread::sleep_for(chrono::milliseconds(1000));


	}

}
