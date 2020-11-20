import java.util.Scanner;

abstract class Q {// queue들
	public abstract int[] RR(int a[], int num, int q);// Round Robin

	public abstract int[] SJF(int a[]);// Shortest Job First

	public abstract int[] SRTF(int a[]);// Preemptive SJF

	public abstract int[] PQ(int a[]);// Priority Queue

	public abstract int[] PPQ(int a[]); // Preemption Priority Queue

	public abstract int[] FIFO(int a[], int arrival[]);// First In First Out
}

class Generate extends Q {// process 생성
	public static int process_num;// 랜덤한 프로세스 개수(1~10)
	public static int process_burst[];
	public static int process_arrival[];
	public static int ready[];
	public static int priority[];
	public static int q_choice; // 큐 스케쥴링 선택(1~4)
	public static int processes_gen2; // 프로세스가 새로 생성됐는지 비교
	public static boolean notReady; // ready에 암것도 없음
	public static int total_time;// switch 일어나기 전 총 시간
	// ======================================result
	public static int execution_time;
	public static int job_RR;
	public static int job_SJF;
	public static int job_PQ;
	public static int job_FIFO;
	public static int context_switch;
	public static int processes_gen;// 생성 프로세스
	public static int processes_com;// 완료 프로세스
	// =====================================question
	public static int tCycles;
	public static int tSlot;
	public static int contextSwitchingTime;
	public static int SJF_pre;
	public static int PQ_pre;
	public static int RR_alpha;
	public static int SJF_alpha;
	public static int PQ_alpha;
	public static int FIFO_alpha;
	public static int RR_aging;
	public static int SJF_aging;
	public static int PQ_aging;
	public static int FIFO_aging;
	public static int RR_init;
	public static int SJF_init;
	public static int PQ_init;
	public static int FIFO_init;
	// =====================================

	public Generate() {
		process_burst = new int[10]; // 프로세스의 burst time
		process_arrival = new int[10]; // 프로세스의 arrival time
		ready = new int[10]; // 최대 arrival시간 만큼, 프로세스 개수만큼 (나중에 고치기)
		priority = new int[10];

	}

	public void Question() {// 질문에 대한 답 입력
		Scanner scanner = new Scanner(System.in);

		System.out.println("Enter the time cycles : ");
		tCycles = scanner.nextInt();
		System.out.println("Enter the value of time slot for RR : ");
		tSlot = scanner.nextInt();
		System.out.println("Enter the context switching time : ");
		contextSwitchingTime = scanner.nextInt();
		System.out.println("SJF with pre-emption(1-yes/0-no) : ");
		SJF_pre = scanner.nextInt();
		System.out.println("PQ with pre-emption ( 1-yes/0-no) : ");
		PQ_pre = scanner.nextInt();
		System.out.println("Enter the alpha co-eff for RR : ");
		RR_alpha = scanner.nextInt();
		System.out.println("Enter the alpha co-eff for SJF : ");
		SJF_alpha = scanner.nextInt();
		System.out.println("Enter the alpha co-eff for PQ : ");
		PQ_alpha = scanner.nextInt();
		System.out.println("Enter the alpha co-eff for FIFO : ");
		FIFO_alpha = scanner.nextInt();
		System.out.println("Enter the aging time for RR : ");
		RR_aging = scanner.nextInt();
		System.out.println("Enter the aging time for SJF : ");
		SJF_aging = scanner.nextInt();
		System.out.println("Enter the aging time for PQ : ");
		PQ_aging = scanner.nextInt();
		System.out.println("Enter the aging time for FIFO : ");
		FIFO_aging = scanner.nextInt();
		System.out.println("Enter the initial estimated time for RR : ");
		RR_init = scanner.nextInt();
		System.out.println("Enter the initial estimated time for SJF : ");
		SJF_init = scanner.nextInt();
		System.out.println("Enter the initial estimated time for PQ : ");
		PQ_init = scanner.nextInt();
		System.out.println("Enter the initial estimated time for FIFO");
		FIFO_init = scanner.nextInt();

	}

	public void setProcess() {
		Generate g = new Generate();
		g.init();
		for (int i = 0; i < process_num; i++) {
			process_burst[i] = (int) (Math.random() * 10) + 1; // 랜덤한 프로세스 burst time(1~10)
			process_arrival[i] = (int) (Math.random() * 10); // 랜덤한 프로세스 arrival time(0~10)
		}
	}

	public void Choice() {
		int i2 = 0;// 큐에 들어감으로 인해 지나간 시간
		Generate g = new Generate();
		g.setProcess();
		g.Question();
		System.out.println("process 만들어진 개수 : " + process_num);// 나중에 지우기
		for (int i = 0; i < 100; i++) {// i는 시간을 뜻함.
			System.out.println("i값 : " + i);
			processes_gen2 = processes_gen; // processes_gen2는 이전 프로세스 생성 개수, processes_gen는 현재 프로세스 생성개수
			for (int j = 0; j < process_num; j++) {// j는 i시간대에 도착한 프로세스 위치
				if (process_arrival[j] >= i && process_arrival[j] <= i2) {// 도착시간이 i인 프로세스를 찾음
					System.out.println("i값 : " + i + ", 그리고" + i2 + ", 그리고" + j );
					System.out.println("process_burst값 : " + process_burst[j]);
					ready[j] = process_burst[j];// i시간대에 j번째 프로세스의 burst time을 저장                                  ***여기서 자꾸 오류남.
					processes_gen = processes_gen + 1;// 프로세스 생성됨
				}
			}
			i = i2;// i2만큼의 프로세스를 다 넣어서 현재 시간을 i2로 변형해줌
			q_choice = (int) ((Math.random() * 4) + 1); // 큐 스케쥴링 선택(1~4)
			System.out.println("choice 값 : "+ q_choice);
			execution_time = 0;// 프로세스 실행 시간 초기화
			if (processes_gen2 == processes_gen) {// 생성된 프로세스가 없으면
				System.out.println("no new process was generated.");
				i2++;// 임시로
				g.result();
			} else if (q_choice == 1) {
				System.out.println("Process appended to FIFO queue.");
				ready = FIFO(ready, process_arrival);
				i2 = i + execution_time;// 임시로
				g.result();

			} else if (q_choice == 2) {
				System.out.println("Process appended to PQ queue.");
				for (int k = 0; k < process_num; k++) {
					priority[k] = (int) (Math.random() * 10) + 1;//우선순위 부여
				}
				if (PQ_pre == 1) {
					ready = PPQ(ready);// 아직 안 함
					i2++;// 임시로

				} else {
					ready = PQ(ready);// 아직 안 함
					i2 = i + execution_time;// 프로세스 하나 돌린 만큼 시간이 지남

				}
				i2++;// 임시로
				g.result();
			} else if (q_choice == 3) {
				System.out.println("Process appended to SJF queue.");
				if (SJF_pre == 1) {
					ready = SRTF(ready);// 아직 안 함
					i2++;// 임시로

				} else {
					ready = SJF(ready);// 아직 안 함
					i2 = i + execution_time;// 프로세스 하나 돌린 만큼 시간이 지남

				}
				g.result();
			} else if (q_choice == 4) {
				System.out.println("Process appended to RR queue.");
				i2 = i + tSlot * (processes_gen - processes_com);// 원래 i시간인데 RR에 들어가면서 실행되고 있는 process의 개수만큼의 tSlot이 지남.
				ready = RR(ready, processes_gen - processes_com, tSlot);
				g.result();
			}
			if (processes_com == process_num) {// 프로세스 모두가 종료되면 반복문 종료
				System.out.println("===================SUMMARY====================");
				System.out.println("==============================================");
				System.out.println("AVERAGE WAITING TIME = ");
				System.out.println("AVERAGE TURNAROUND TIME = ");
				System.out.println("CPU UTILIZATION  = ");
				System.out.println("MAXIMUM TURNAROUND TIME = ");
				System.out.println("MAXIMUM WAIT TIME = ");
				System.out.println("CPU THROUGHPUT = ");

				break;
			}

		}
		// 나중에 지우기==============================
		System.out.println(tCycles + "," + tSlot + "," + contextSwitchingTime + "," + SJF_pre + "," + PQ_pre + ","
				+ RR_alpha + "," + SJF_alpha + "," + PQ_alpha + "," + FIFO_alpha + "," + RR_aging + "," + SJF_aging
				+ "," + PQ_aging + "," + FIFO_aging + "," + RR_init + "," + SJF_init + "," + PQ_init + "," + FIFO_init);
		System.out.println("process_num: " + process_num + " /ready[0] 값:" + ready[0] + " /ready[1] 값: " + ready[1]
				+ " /ready[2] 값: " + ready[2] + " /ready[3] 값: " + ready[3] + " /ready[4] 값: " + ready[4]);
		System.out.println("ready[5] 값:" + ready[5] + " /ready[6] 값: " + ready[6] + " /ready[7] 값: " + ready[7]
				+ " /ready[8] 값: " + ready[8] + " /ready[9] 값: " + ready[9]);
		System.out.println("process_burst[0] 값:" + process_burst[0] + " /process_burst[1] 값: " + process_burst[1]
				+ " /process_burst[2] 값: " + process_burst[2] + " /process_burst[3] 값: " + process_burst[3]
				+ " /process_burst[4] 값: " + process_burst[4]);
		System.out.println("process_burst[5] 값:" + process_burst[5] + " /process_burst[6] 값: " + process_burst[6]
				+ " /process_burst[7] 값: " + process_burst[7] + " /process_burst[8] 값: " + process_burst[8]
				+ " /process_burst[9] 값: " + process_burst[9]);
		// 나중에 지우기==============================
	}

	public void init() {// 초기화
		process_num = (int) (Math.random() * 10) + 1;// 랜덤한 프로세스 개수(1~10)
		process_burst = new int[10];
		process_arrival = new int[10];
		priority = new int[10];
		ready = new int[10];
		processes_gen = 0; // 프로세스 생성된 개수
		processes_gen2 = 0; // 프로세스가 새로 생성됐는지 비교
		total_time = 0;
		execution_time = 0;
		job_RR = 0;
		job_SJF = 0;
		job_PQ = 0;
		job_FIFO = 0;
		context_switch = 0;
		processes_com = 0;
	}

	public void result() {
		if (processes_gen2 != processes_gen) {
			System.out.println("Process execution time = " + execution_time);
		}
		System.out.println("# of jobs in RR = " + job_RR);
		System.out.println("# of jobs in SJF = " + job_SJF);
		System.out.println("# of jobs in PQ = " + job_PQ);
		System.out.println("# of jobs in FIFO = " + job_FIFO);
		System.out.println("# context switches = " + context_switch);
		System.out.println("# Total processes generated = " + processes_gen);
		System.out.println("# Total processes completed = " + processes_com);
		System.out.println("==============================================");
	}

	@Override
	public int[] RR(int[] a, int num, int quantum) {// ready에 있는 process, quantum값
		job_RR++;// RR이 실행된 횟수
		int ready[] = new int[10];
		int num_check = 0;
		ready = a;
		for (int i = 0; i < 10; i++) {
			if (a[i] > quantum) {
				ready[i] = a[i] - quantum;
				context_switch += 1; // 아직 연구중
				execution_time += quantum; // 아직 연구중

			} else {
				ready[i] = 0;
				num_check++;
			}
		}
		System.out.println("num_check = " + num_check);
		if (num_check == 10) {// 모든 프로세스가 종료되면
			notReady = true;
		}
		processes_com += num - (10 - num_check);// 종료된 process 개수 = 원래 종료된 process+(현재 실행 process-(10-ready값 0인개수)
		return ready;
	}

	@Override
	public int[] SJF(int[] a) {
		job_SJF++;
		int ready[] = new int[10];
		int num_check = 0;
		ready = a;
		int j = 0;
		for (j = 0; j < 10; j++) {
			if (a[j] != 0) {
				break;
			} else {
				num_check++;// burst time이 0인 프로세스의 개수
			}
		}
		for (int i = j; i < 10; i++) {
			if (a[i] != 0) {
				if (a[j] >= a[i]) {
					j = i;
				}
			} else if (a[i] == 0) {
				num_check++;
			}

		}
		context_switch += 1;
		execution_time = ready[j];

		if (num_check == 10) {// 모든 프로세스가 종료되면
			notReady = true;
		} else {
			processes_com += 1; // 프로세스를 하나씩만 돌릴거기 때문에
		}
		ready[j] = 0;
		return ready;
	}

	@Override
	public int[] SRTF(int[] a) {
		job_SJF++;
		return null;
	}

	@Override
	public int[] PQ(int[] a) {
		job_PQ++;
		return null;
	}

	@Override
	public int[] PPQ(int[] a) {
		job_PQ++;
		return null;
	}

	@Override
	public int[] FIFO(int[] a, int[] arrival) {
		job_FIFO++;
		int ready[] = new int[10];
		int i=0;
		ready = a;
		int low_arri = 99;
		int execute = 0;
		for(i=0;i<10;i++) {
			if(ready[i]!=0 &&arrival[i]<low_arri) {//burst time이 0이 아니면서 출발 시간이 가장 빠른 것
				execute = i;
				low_arri = arrival[i];
			}
		}
		context_switch += 1;
		execution_time = ready[execute];
		ready[execute] = 0;
		processes_com += 1;
		return ready;
	}
}

public class MLFQ {

	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		Generate g = new Generate();
		while (true) {
			g.Choice();
			System.out.println("종료하시겠습니까? (1-yes) : ");
			int terminated = scanner.nextInt();
			if (terminated == 1) {
				break;
			}
		}

	}
}
