#define _CRT_SECURE_NO_WARNINGS
#define SIZE 50 //프로세스 개수
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>//사이클 끝나면 큐 바꿔 줌. age도 늘려줌.
int RR_q(int* RR, int* time, int* time_sum, int* quantum, int* tCycle, bool* terminated, int* processes_com, int*process_end, bool* generate, int* process_arrival, int* processes_gen, int* burst_change);
int SJF_q(int* SJF, int* time, int* time_sum, bool* terminated, int* processes_com, int* process_end, bool* generate, int* process_arrival, int* processes_gen, int* burst_change);
int SRTF_q(int* SRTF, int* time, int* time_sum, bool* terminated, int* processes_com, int* process_end, bool* generate, int* process_arrival, int* processes_gen, int* burst_change);
int PQ_q(int* PQ, int*priority, int* time, int* time_sum, bool* terminated, int* processes_com, int* process_end, bool* generate, int* process_arrival, int* processes_gen, int* burst_change);
int PPQ_q(int* PPQ, int* priority, int* time, int* time_sum, bool* terminated, int* processes_com, int* process_end, bool* generate, int* process_arrival, int* processes_gen, int* burst_change);
int FIFO_q(int* FIFO, int* arrival, int* time, int* time_sum, bool* terminated, int* processes_com, int* process_end, bool* generate, int* processes_gen, int* burst_change);
///////////////////////////////////////////////////////////////////////////

void result(int, int, int, int, int, int ,int);//결과 출력
void question(int* a,int*b, int*c, int*d,int* e, int* f, int* g, int* h, int* i, int* j, int* k, int* l, int* m,int* n, int*o, int* p, int* q); //질문 불러오기
void init(int*, int*, int*, int*, int*, int*, int*);//초기화
void setProcess(int*, int*, int*, int*); //프로세스 생성
int nextBurstTime(int coeff, int alpha, int init_time);//burstTime 예상
void boolean(bool* terminated, bool* waiting);// 프로세스가 실행됐는지, 프로세스가 종료됐는지
void summary(int average_waiting_time, int average_turnaround_time, int cpu_utilization, int max_turnaround_time, int max_wait_time, int cpu_throughput);//요약
void calculate(int* average_waiting_time, int* average_turnaround_time, int* cpu_utilization, int* max_turnaround_time, int* max_wait_time, int* cpu_throughput, int time_sum, int* process_arrival,int* process_end, int* process_burst, int idle_time);//계산
void age(int* RR, int* SJF, int* PQ, int* FIFO, int* process_arrival, int time_sum, int RR_aging, int SJF_aging, int PQ_aging, int FIFO_aging);//priority 늘려줌

//////////////////////////////////////////////////////////////////////////
int main(void) {
	int tCycles, tSlot, contextSwitchingTime, SJF_pre, PQ_pre, RR_alpha, SJF_alpha, PQ_alpha, FIFO_alpha, RR_aging, SJF_aging, PQ_aging, FIFO_aging, RR_init, SJF_init, PQ_init, FIFO_init;//질문들
	int job_RR=0, job_SJF=0, job_PQ=0, job_FIFO=0, context_switch=0, processes_gen=0, processes_com=0;//결과물
	int process_burst[SIZE] = { 0 }, process_arrival[SIZE] = { 0 }, priority[SIZE] = { 0 }, queue_choice[SIZE] = { 0 }, process_end[SIZE] = { 0 };//랜덤 값을 주기 위해 만든 것
	int RR[SIZE] = { 0 },SJF[SIZE] = { 0 }, PQ[SIZE] = { 0 }, FIFO[SIZE] = { 0 };//큐마다 process가 ready상태임
	int burst_change[SIZE] = { 0 };//실행 후 바뀐 burst_time
	int average_waiting_time = 0, average_turnaround_time = 0, cpu_utilization = 0, max_turnaround_time = 0, max_wait_time = 0, cpu_throughput = 0;//summary
	int RR_put = 0, PQ_put = 0, FIFO_put = 0, SJF_put = 0;
	int time = 0, time_sum = 0;//time은 Cycle을 주기로 세고, time_sum은 전체 시간을 말함.
	bool terminated[SIZE];//process가 종료 됐음을 표시
	bool generate[SIZE];//waiting 상태임을 표시
	bool pre_input = false, pre_input2 = false;
	int i, location;//위치 나타내는 애들

	//////////////////////////////////////////////
	init(&job_RR, &job_SJF, &job_PQ, &job_FIFO, &context_switch, &processes_gen, &processes_com);//결과 초기화
	question(&tCycles, &tSlot, &contextSwitchingTime, &SJF_pre, &PQ_pre, &RR_alpha, &SJF_alpha, &PQ_alpha, &FIFO_alpha, &RR_aging, &SJF_aging, &PQ_aging, &FIFO_aging, &RR_init, &SJF_init, &PQ_init, &FIFO_init);//질문 초기화
	setProcess(&process_burst, &process_arrival, &priority, &queue_choice);//프로세스 생성
	boolean(&terminated, &generate);//프로세스 상태 초기화
	for (i = 0; i < SIZE; i++) {
		burst_change[i] = process_burst[i];
	}
	//nextBurstTime(SJF_alpha, 0.5, SJF_init);
	//////////////////////////////////////////////

	for (i = 0; i < SIZE; i++) {//프로세스들이 들어갈 큐 종류
		if (queue_choice[i] == 1) {
			RR[i] = process_burst[i];
			RR_put++;
		}
		else if (queue_choice[i] == 2) {
			SJF[i] = process_burst[i];
			SJF_put++;

		}
		else if (queue_choice[i] == 3) {
			PQ[i] = process_burst[i];
			PQ_put++;
		}
		else if (queue_choice[i] == 4) {
			FIFO[i] = process_burst[i];
			FIFO_put++;
		}
	}
	while (1) {
		for (i = 0; i < SIZE; i++) {//프로세스 개수만큼 돌려줌.
			if (process_arrival[i] <= time_sum && burst_change[i] != 0) {//상위 큐부터 도착시간이 지금의 시간을 넘지 않고, burst time 있는 process를 찾음.
				if (RR[i] != 0) {//지금시간 전에 들어와있는 애가 상위 큐의 애라면 돌려줌.
					pre_input = false;
					pre_input2 = false;
					context_switch++;
					location = RR_q(&RR, &time, &time_sum, &tSlot, &tCycles, &terminated, &processes_com, &process_end, &generate, &process_arrival, &processes_gen, &burst_change);
					SJF[location] = RR[location];//SJF로 넘겨줌
					burst_change[location] = RR[location];
					RR[location] = 0;//RR에서 종료 또는 나옴.
					job_RR++;
					result(job_RR, job_SJF, job_PQ, job_FIFO, context_switch, processes_gen, processes_com, &processes_gen);//결과 출력 
				}
				else if (SJF[i] != 0) {
					if (SJF_pre == 1) {//pre-emptive, context switch 고민중
						location = SRTF_q(&SJF, &time, &time_sum, &terminated, &processes_com, &process_end, &generate, &process_arrival, &processes_gen, &burst_change);
						if (pre_input == false) {
							job_SJF++;
							context_switch++;
							result(job_RR, job_SJF, job_PQ, job_FIFO, context_switch, processes_gen, processes_com, &processes_gen);//결과 출력 
						}
						if (SJF[location] == 0) {
							pre_input = false;
							result(job_RR, job_SJF, job_PQ, job_FIFO, context_switch, processes_gen, processes_com, processes_gen);//결과 출력 
						}
						pre_input = true;
						pre_input2 = false;
					}
					else {
						context_switch++;
						location = SJF_q(&SJF, &time, &time_sum, &terminated, &processes_com, &process_end, &generate, &process_arrival, &processes_gen, &burst_change);
						job_SJF++;
						result(job_RR, job_SJF, job_PQ, job_FIFO, context_switch, processes_gen, processes_com, processes_gen);//결과 출력
						pre_input = false;
						pre_input2 = false;
					}
				}
				else if (PQ[i] != 0) {
					if (PQ_pre == 1) {
						location = PPQ_q(&PQ, &priority, &time, &time_sum, &terminated, &processes_com, &process_end, &generate, &process_arrival, &processes_gen, &burst_change);
						if (pre_input2 == false) {
							job_PQ++;
							context_switch++;
							result(job_RR, job_SJF, job_PQ, job_FIFO, context_switch, processes_gen, processes_com, processes_gen);//결과 출력
						}
						if (PQ[location] == 0) {
							pre_input2 = false;
							result(job_RR, job_SJF, job_PQ, job_FIFO, context_switch, processes_gen, processes_com, processes_gen);//결과 출력
						}
						pre_input = false;
						pre_input2 = true;
					}
					else {
						context_switch++;
						location = PQ_q(&PQ, &priority, &time, &time_sum, &terminated, &processes_com, &process_end, &generate, &process_arrival, &processes_gen, &burst_change);
						job_PQ++;
						result(job_RR, job_SJF, job_PQ, job_FIFO, context_switch, processes_gen, processes_com, &processes_gen);//결과 출력
						pre_input = false;
						pre_input2 = false;
					}
				}
				else if (FIFO[i] != 0) {
					context_switch++;
					location = FIFO_q(&FIFO, &process_arrival, &time, &time_sum, &terminated, &processes_com, &process_end, &generate, &processes_gen, &burst_change);
					job_FIFO++;
					result(job_RR, job_SJF, job_PQ, job_FIFO, context_switch, processes_gen, processes_com, &processes_gen);//결과 출력
					pre_input = false;
					pre_input2 = false;
				}
				else {
					printf("no new process was generated\n");
					result(job_RR, job_SJF, job_PQ, job_FIFO, context_switch, processes_gen, processes_com, &processes_gen);//결과 출력
				}
			}
			else {
				time_sum++;
				time++;
			}
			if (processes_com >= SIZE) {
				break;
			}
		}
		if (time > tCycles) {//모든 프로세스가 나이를 먹어야하고,
			time = time - tCycles;
			age(&RR, &SJF, &PQ, &FIFO, &process_arrival, time_sum, RR_aging, SJF_aging, PQ_aging, FIFO_aging);
		}
		if (processes_com >= SIZE) {
			break;
		}
	}
	int idle_time = contextSwitchingTime * context_switch;
	calculate(&average_waiting_time, &average_turnaround_time, &cpu_utilization, &max_turnaround_time, &max_wait_time, &cpu_throughput, time_sum, &process_arrival, &process_end, &process_burst, idle_time);
	summary(average_waiting_time, average_turnaround_time, cpu_utilization, max_turnaround_time, max_wait_time, cpu_throughput);

	return 0;
}
//메인 끝========================================================================

void question(int* tCycles, int* tSlot, int* contextSwitchingTime , int* SJF_pre, int* PQ_pre, int* RR_alpha, int* SJF_alpha, int* PQ_alpha, int* FIFO_alpha, int* RR_aging, int* SJF_aging, int* PQ_aging, int* FIFO_aging, int* RR_init, int* SJF_init, int* PQ_init, int* FIFO_init) {
	printf("Enter the time cycles :");
	scanf("%d", tCycles);
	printf("Enter the value of time slot for RR : ");
	scanf("%d", tSlot);
	printf("Enter the context switching time : ");
	scanf("%d", contextSwitchingTime);
	printf("SJF with pre-emption (1-yes/0-no) : ");
	scanf("%d", SJF_pre);
	printf("PQ with pre-emption (1-yes/0-no) : ");
	scanf("%d", PQ_pre);
	printf("Enter the alpha co-eff for RR : ");
	scanf("%d", RR_alpha);
	printf("Enter the alpha co-eff for SJF : ");
	scanf("%d", SJF_alpha);
	printf("Enter the alpha co-eff for PQ : ");
	scanf("%d", PQ_alpha);
	printf("Enter the alpha co-eff for FIFO : ");
	scanf("%d", FIFO_alpha);
	printf("Enter the aging time for RR : ");
	scanf("%d", RR_aging);
	printf("Enter the aging time for SJF : ");
	scanf("%d", SJF_aging);
	printf("Enter the aging time for PQ : ");
	scanf("%d", PQ_aging);
	printf("Enter the aging time for FIFO : ");
	scanf("%d", FIFO_aging);
	printf("Enter the initial estimated time for RR : ");
	scanf("%d", RR_init);
	printf("Enter the initial estimated time for SJF : ");
	scanf("%d", SJF_init);
	printf("Enter the initial estimated time for PQ : ");
	scanf("%d", PQ_init);
	printf("Enter the initial estimated time for FIFO : ");
	scanf("%d", FIFO_init);
}
void result(int job_RR, int job_SJF, int job_PQ, int job_FIFO, int context_switch, int processes_gen, int processes_com) {
	printf("# of jobs in RR = %d\n", job_RR);
	printf("# of jobs in SJF = %d\n", job_SJF);
	printf("# of jobs in PQ = %d\n", job_PQ);
	printf("# of jobs in FIFO = %d\n", job_FIFO);
	printf("# context switches = %d\n", context_switch);
	printf("# Total processes generated = %d\n", processes_gen);
	printf("# Total processes completed = %d\n", processes_com);
	printf("==============================================\n");
}
void summary(int average_waiting_time, int average_turnaround_time, int cpu_utilization, int max_turnaround_time, int max_wait_time, int cpu_throughput) {
	printf("\nSUMMARY\n\n");
	printf("==============================================\n");
	printf("AVERAGE WAITING TIME = %d time units\n",average_waiting_time);
	printf("AVERAGE TURNAROUND TIME = %d time units\n", average_turnaround_time);
	printf("CPU UTILIZATION = %d %%\n", cpu_utilization);
	printf("MAXIMUM TURNAROUND TIME = %d time units\n", max_turnaround_time);
	printf("MAXIMUM WAIT TIME = %d time units\n", max_wait_time);
	printf("CPU THROUGHPUT = %d %%\n", cpu_throughput);
}
void init(int* job_RR, int* job_SJF, int* job_PQ, int* job_FIFO, int* context_switch, int* processes_gen, int* processes_com) {
	*job_RR = 0, *job_SJF = 0, *job_PQ = 0, *job_FIFO = 0, *context_switch = 0, *processes_gen = 0, *processes_com = 0;//완벽
}

void boolean(bool* terminated, bool* waiting) {//처음에는 모든 process가 실행도, 종료도 안 함.
	int i;

	for (i = 0; i < SIZE; i++) {
		terminated[i] = false;
	}
	for (i = 0; i < SIZE; i++) {
		waiting[i] = false;
	}


}
void setProcess(int* process_burst, int* process_arrival, int* priority, int* queue_choice) {//나중에 랜덤값 집어넣기
	//여기 있는거 다 임의로 지정 했음. 나중에 랜덤값으로 바꿀거임.
	int i;
	int j = 0;
	//1~100개 중 랜덤으로 생성

	for (i = 0; i < SIZE; i++) {
		process_burst[i] = (rand()%50)+1; //1~100
	}
	for (i = 0; i < SIZE; i++) {
		
		process_arrival[i] = (rand() % 100) + 1; //1~100
		
	}
	for (i = 0; i < SIZE; i++) {
		priority[i] = (rand() % 5) + 1; //1,2,3,4,5 중 하나

	}
	for (i = 0; i < SIZE; i++) {
		queue_choice[i] = (rand() % 4) + 1; //1,2,3,4 중 하나

	}

}

int nextBurstTime(int coeff, int alpha, int init_time) {//시간 예상해서 돌려줌. 알파값 어떻게 할 지 고민중
	int nextTime;
	nextTime = coeff* alpha + (1 - alpha) * init_time;

	return nextTime;
}
//큐 시작========================================================================
int RR_q(int* RR, int* time, int* time_sum, int* quantum, int* tCycle, bool* terminated, int* processes_com, int* process_end, bool* generate, int* process_arrival, int* processes_gen, int* burst_change) {// 돌렸는데 안 끝난 프로세스 어떻게 할 지 고민중
	//리턴 값을 RR로 해줄까? 그러고 SJF에 넘기고,, 원래 RR은 비우고!
	int i = 0;
	int j = 0;

	for (i = 0; i < SIZE; i++) {//프로세스 하나만 실행시킬거임
		if (RR[i] != 0 && process_arrival[i] <= *time_sum) {//burst time이 0이 아니면서 Pid가 가장 작은 process를 실행시킴. 다 못 끝내면 얘는 SJF큐로 들어감.
			if (RR[i] > *quantum) {
				if (generate[i] == false) {//처음 돌리는거면 큐에 추가 됐음을 알려줌.
					printf("Process appended to RR queue.\n");
					printf("Process execution time = %d\n", RR[i]);
					generate[i] = true;// 큐에 들어갔었음을 의미함.
					*processes_gen += 1;
				}
				else {
					printf("no new process was generated\n");
				}
				RR[i] -= *quantum;//일단 RR값 quantum만큼 줄임.
				*time += *quantum;//시간 quantum만큼 올림.
				*time_sum += *quantum;//전체 시간도 quantum만큼 올림.
				break;
			}
			else {//quantum값보다 작기 때문에 burst time만큼 시간 증가
				*time += RR[i];
				*time_sum += RR[i];
				process_end[i] = *time_sum;// 이 프로세스가 종료한 시간
				RR[i] = 0;
				burst_change[i] = 0;
				terminated[i] = true;//프로세스 종료
				*processes_com += 1;//프로세스 종료한 개수
				break;
			}
		}
	}
	return i;//위치 돌려줌.
}

//SJF는 burst가 가장 작은 애 먼저 돌림. //process하나만 돌리고 나와서 다시 넣고 나와서 넣고 나와서 어쩌고 저쩌고 할거임.
int SJF_q(int* SJF, int* time, int* time_sum, bool* terminated, int* processes_com, int* process_end, bool* generate, int* process_arrival, int* processes_gen, int* burst_change) {//아직 만드는 중 //SJF는 SJF에 들어간 프로세스들//시간대별로 추가시킴.//추가할 거 있음// SJF에 들어가면 꼭 종료됨. 유가릿?
	int i = 0;
	int j = 0;//실행할 process 위치 저장
	int burst_min = 9999;//burst가 가장 작은 processs
	
	for (i = 0; i < SIZE; i++) {//프로세스 하나만 실행시킬거임
		if (burst_min > SJF[i] && SJF[i] != 0 && process_arrival[i] <= *time_sum) {//burst time이 0이 아니면서 가장 작은 process를 실행시킴.
			burst_min = SJF[i];
			j = i;
		}
	}
	if (generate[j] == false) {//처음 돌리는거면 큐에 추가 됐음을 알려줌.
		printf("Process appended to SJF queue.\n");
		printf("Process execution time = %d\n", SJF[j]);
		generate[j] = true;// 큐에 들어갔었음을 의미함.
		*processes_gen += 1;
	}
	else {
		printf("no new process was generated\n");
	}
	*time += burst_min;
	*time_sum += burst_min;
	process_end[j] = *time_sum; //이 프로세스가 종료한 시간
	SJF[j] = 0;
	burst_change[j] = 0;
	terminated[j] = true; // 종료됨을 표시
	*processes_com += 1; //사용할 곳 나중에
		

	return j;// 프로세스 위치 돌려줌.
}

//SRTF는 burst가 가장 작은 애 먼저 돌림. pre-emptive임. 지금 가장 문제!!! 얘는 switching을 어떻게 해줘야 할 지 문제!!
int SRTF_q(int* SJF, int* time, int* time_sum, bool* terminated, int* processes_com, int* process_end, bool* generate, int* process_arrival, int* processes_gen, int* burst_change) {//아직 만드는 중 //SJF는 SJF에 들어간 프로세스들//추가할 거 있음
	int i = 0;
	int j = 0;//실행할 process 위치 저장
	int burst_min = 9999;//burst가 가장 작은 processes

	for (i = 0; i < SIZE; i++) {//프로세스 하나만 실행시킬거임
		if (burst_min > SJF[i] && SJF[i] != 0 && process_arrival[i] <= *time_sum) {//burst time이 0이 아니면서 가장 작은 process를 실행시킴.
			burst_min = SJF[i];
			j = i;
		}
	}
	if (generate[j] == false) {//처음 돌리는거면 큐에 추가 됐음을 알려줌.
		printf("Process appended to SJF queue.\n");
		printf("Process execution time = %d\n", SJF[j]);
		generate[j] = true;// 큐에 들어갔었음을 의미함.
		*processes_gen += 1;
	}
	else {
		//printf("no new process was generated\n");
	}
	SJF[j] -= 1;//얘는 1씩 감소하면서 지켜볼거임.
	burst_change[j] -= 1;
	*time += 1;// 이게 되는지 몰겠다
	*time_sum += 1;
	if (SJF[j] == 0) {
		process_end[j] = *time_sum; //이 프로세스가 종료한 시간
		terminated[j] = true; // 종료됨을 표시
		*processes_com +=1; //사용할 곳 나중에
	}
	return j;// 프로세스 위치 돌려줌.
}


int PQ_q(int* PQ, int* priority, int* time, int* time_sum, bool* terminated, int* processes_com, int* process_end, bool* generate, int* process_arrival, int* processes_gen, int* burst_change) {
	int i = 0;
	int j = 0;//실행할 process 위치 저장
	int priority_min = 9999;//priority가 가장 작은 processs

	for (i = 0; i < SIZE; i++) {//프로세스 하나만 실행시킬거임
		if (priority_min > priority[i] && PQ[i] != 0 && process_arrival[i] <= *time_sum) {//burst time이 0이 아니면서 가장 작은 process를 실행시킴.
			priority_min = priority[i];
			j = i;
		}
	}
	if (generate[j] == false) {//처음 돌리는거면 큐에 추가 됐음을 알려줌.
		printf("Process appended to PQ queue.\n");
		printf("Process execution time = %d\n", PQ[j]);
		generate[j] = true;// 큐에 들어갔었음을 의미함.
		*processes_gen += 1;
	}
	else {
		printf("no new process was generated\n");
	}
	*time += PQ[j];
	*time_sum += PQ[j];
	PQ[j] = 0;
	burst_change[j] = 0;
	process_end[j] = *time_sum; //이 프로세스가 종료한 시간
	terminated[j] = true; // 종료됨을 표시
	*processes_com +=1;

	return j;// 프로세스 위치 돌려줌.

}
int PPQ_q(int* PQ, int* priority, int* time, int* time_sum, bool* terminated, int* processes_com, int* process_end, bool* generate, int* process_arrival, int* processes_gen, int* burst_change) {
	int i = 0;
	int j = 0;//실행할 process 위치 저장
	int priority_min = 9999;//priority가 가장 작은 processes

	for (i = 0; i < SIZE; i++) {//프로세스 하나만 실행시킬거임
		if (priority_min > priority[i] && PQ[i] != 0 && process_arrival[i] <= *time_sum) {//burst time이 0이 아니면서 가장 작은 process를 실행시킴.
			priority_min = priority[i];
			j = i;
		}
	}
	if (generate[j] == false) {//처음 돌리는거면 큐에 추가 됐음을 알려줌.
		printf("Process appended to PQ queue.\n");
		printf("Process execution time = %d\n", PQ[j]);
		generate[j] = true;// 큐에 들어갔었음을 의미함.
		*processes_gen += 1;
	}
	else {
		//printf("no new process was generated\n");
	}

	PQ[j] -= 1;//얘는 1씩 감소하면서 지켜볼거임.
	burst_change[j] -= 1;
	*time += 1;// 이게 되는지 몰겠다
	*time_sum += 1;
	if (PQ[j] == 0) {
		process_end[j] = *time_sum; //이 프로세스가 종료한 시간
		terminated[j] = true;
		*processes_com +=1;
	}
	return j;// 프로세스 위치 돌려줌. 
}

int FIFO_q(int* FIFO, int* arrival, int* time, int* time_sum, bool* terminated, int* processes_com, int* process_end, bool* generate, int* processes_gen, int* burst_change) {
	int i = 0;
	int j = 0;//실행할 process 위치 저장
	int arrival_min = 9999;//arrival가 가장 작은 processs

	for (i = 0; i < SIZE; i++) {//프로세스 하나만 실행시킬거임
		if (arrival_min >arrival[i] && FIFO[i] != 0 && arrival[i] <= *time_sum) {//burst time이 0이 아니면서 가장 작은 process를 실행시킴.
			arrival_min = arrival[i];
			j = i;
		}
	}
	if (generate[j] == false) {//처음 돌리는거면 큐에 추가 됐음을 알려줌.
		printf("Process appended to FIFO queue.\n");
		printf("Process execution time = %d\n", FIFO[j]);
		generate[j] = true;// 큐에 들어갔었음을 의미함.
		*processes_gen += 1;
	}
	else {
		printf("no new process was generated\n");
	}
	*time += FIFO[j];
	*time_sum += FIFO[j];
	FIFO[j] = 0;
	burst_change[j] = 0;
	process_end[j] = *time_sum; //이 프로세스가 종료한 시간
	terminated[j] = true; // 종료됨을 표시
	*processes_com +=1;

	return 0;
}
void calculate(int* average_waiting_time, int* average_turnaround_time, int* cpu_utilization, int* max_turnaround_time, int* max_wait_time, int* cpu_throughput, int time_sum, int *process_arrival, int *process_end, int* process_burst, int idle_time) {
	int i;
	int waiting_time[SIZE] = { 0 };
	int waiting_time_sum = 0;
	int waiting_time_max = 0;
	int turnaround_time[SIZE] = { 0 };
	int turnaround_time_sum = 0;
	int turnaround_time_max = 0;
	int cpu_cal = 0, cpu_cal2 = 0;
	for (i = 0; i < SIZE; i++) {
		turnaround_time[i] = process_end[i] - process_arrival[i];
		turnaround_time_sum += turnaround_time[i];
		if (turnaround_time_max < turnaround_time[i]) {
			turnaround_time_max = turnaround_time[i];
		}
	}
	for (i = 0; i < SIZE; i++) {
		waiting_time[i] = turnaround_time[i]-process_burst[i];
		waiting_time_sum += waiting_time[i];
		if (waiting_time_max < waiting_time[i]) {
			waiting_time_max = waiting_time[i];
		}
	}

	*average_waiting_time = waiting_time_sum / SIZE;
	*average_turnaround_time = turnaround_time_sum / SIZE;
	*cpu_utilization = (turnaround_time_sum * 100) / (turnaround_time_sum + idle_time);
	*max_turnaround_time = turnaround_time_max;
	*max_wait_time = waiting_time_max;
	*cpu_throughput = (SIZE / turnaround_time_sum) *100;
}
void age(int* RR, int* SJF, int* PQ, int* FIFO, int* process_arrival,int time_sum, int RR_aging, int SJF_aging, int PQ_aging, int FIFO_aging) {
	int i = 0;

	for (i = 0; i < SIZE; i++) {
		if ((time_sum - process_arrival[i]) > SJF_aging && SJF[i] !=0) {
			RR[i] = SJF[i];
			SJF[i] = 0;
		}
	}
	for (i = 0; i < SIZE; i++) {
		if ((time_sum - process_arrival[i]) > PQ_aging && PQ[i] != 0) {
			SJF[i] = PQ[i];
			PQ[i] = 0;
		}
	}
	for (i = 0; i < SIZE; i++) {
		if ((time_sum - process_arrival[i]) > FIFO_aging && FIFO[i] != 0) {
			PQ[i] = FIFO[i];
			FIFO[i] = 0;
		}
	}
	

}