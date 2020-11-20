import java.util.Scanner;

abstract class Q {// queue��
	public abstract int[] RR(int a[], int num, int q);// Round Robin

	public abstract int[] SJF(int a[]);// Shortest Job First

	public abstract int[] SRTF(int a[]);// Preemptive SJF

	public abstract int[] PQ(int a[]);// Priority Queue

	public abstract int[] PPQ(int a[]); // Preemption Priority Queue

	public abstract int[] FIFO(int a[], int arrival[]);// First In First Out
}

class Generate extends Q {// process ����
	public static int process_num;// ������ ���μ��� ����(1~10)
	public static int process_burst[];
	public static int process_arrival[];
	public static int ready[];
	public static int priority[];
	public static int q_choice; // ť �����층 ����(1~4)
	public static int processes_gen2; // ���μ����� ���� �����ƴ��� ��
	public static boolean notReady; // ready�� �ϰ͵� ����
	public static int total_time;// switch �Ͼ�� �� �� �ð�
	// ======================================result
	public static int execution_time;
	public static int job_RR;
	public static int job_SJF;
	public static int job_PQ;
	public static int job_FIFO;
	public static int context_switch;
	public static int processes_gen;// ���� ���μ���
	public static int processes_com;// �Ϸ� ���μ���
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
		process_burst = new int[10]; // ���μ����� burst time
		process_arrival = new int[10]; // ���μ����� arrival time
		ready = new int[10]; // �ִ� arrival�ð� ��ŭ, ���μ��� ������ŭ (���߿� ��ġ��)
		priority = new int[10];

	}

	public void Question() {// ������ ���� �� �Է�
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
			process_burst[i] = (int) (Math.random() * 10) + 1; // ������ ���μ��� burst time(1~10)
			process_arrival[i] = (int) (Math.random() * 10); // ������ ���μ��� arrival time(0~10)
		}
	}

	public void Choice() {
		int i2 = 0;// ť�� ������ ���� ������ �ð�
		Generate g = new Generate();
		g.setProcess();
		g.Question();
		System.out.println("process ������� ���� : " + process_num);// ���߿� �����
		for (int i = 0; i < 100; i++) {// i�� �ð��� ����.
			System.out.println("i�� : " + i);
			processes_gen2 = processes_gen; // processes_gen2�� ���� ���μ��� ���� ����, processes_gen�� ���� ���μ��� ��������
			for (int j = 0; j < process_num; j++) {// j�� i�ð��뿡 ������ ���μ��� ��ġ
				if (process_arrival[j] >= i && process_arrival[j] <= i2) {// �����ð��� i�� ���μ����� ã��
					System.out.println("i�� : " + i + ", �׸���" + i2 + ", �׸���" + j );
					System.out.println("process_burst�� : " + process_burst[j]);
					ready[j] = process_burst[j];// i�ð��뿡 j��° ���μ����� burst time�� ����                                  ***���⼭ �ڲ� ������.
					processes_gen = processes_gen + 1;// ���μ��� ������
				}
			}
			i = i2;// i2��ŭ�� ���μ����� �� �־ ���� �ð��� i2�� ��������
			q_choice = (int) ((Math.random() * 4) + 1); // ť �����층 ����(1~4)
			System.out.println("choice �� : "+ q_choice);
			execution_time = 0;// ���μ��� ���� �ð� �ʱ�ȭ
			if (processes_gen2 == processes_gen) {// ������ ���μ����� ������
				System.out.println("no new process was generated.");
				i2++;// �ӽ÷�
				g.result();
			} else if (q_choice == 1) {
				System.out.println("Process appended to FIFO queue.");
				ready = FIFO(ready, process_arrival);
				i2 = i + execution_time;// �ӽ÷�
				g.result();

			} else if (q_choice == 2) {
				System.out.println("Process appended to PQ queue.");
				for (int k = 0; k < process_num; k++) {
					priority[k] = (int) (Math.random() * 10) + 1;//�켱���� �ο�
				}
				if (PQ_pre == 1) {
					ready = PPQ(ready);// ���� �� ��
					i2++;// �ӽ÷�

				} else {
					ready = PQ(ready);// ���� �� ��
					i2 = i + execution_time;// ���μ��� �ϳ� ���� ��ŭ �ð��� ����

				}
				i2++;// �ӽ÷�
				g.result();
			} else if (q_choice == 3) {
				System.out.println("Process appended to SJF queue.");
				if (SJF_pre == 1) {
					ready = SRTF(ready);// ���� �� ��
					i2++;// �ӽ÷�

				} else {
					ready = SJF(ready);// ���� �� ��
					i2 = i + execution_time;// ���μ��� �ϳ� ���� ��ŭ �ð��� ����

				}
				g.result();
			} else if (q_choice == 4) {
				System.out.println("Process appended to RR queue.");
				i2 = i + tSlot * (processes_gen - processes_com);// ���� i�ð��ε� RR�� ���鼭 ����ǰ� �ִ� process�� ������ŭ�� tSlot�� ����.
				ready = RR(ready, processes_gen - processes_com, tSlot);
				g.result();
			}
			if (processes_com == process_num) {// ���μ��� ��ΰ� ����Ǹ� �ݺ��� ����
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
		// ���߿� �����==============================
		System.out.println(tCycles + "," + tSlot + "," + contextSwitchingTime + "," + SJF_pre + "," + PQ_pre + ","
				+ RR_alpha + "," + SJF_alpha + "," + PQ_alpha + "," + FIFO_alpha + "," + RR_aging + "," + SJF_aging
				+ "," + PQ_aging + "," + FIFO_aging + "," + RR_init + "," + SJF_init + "," + PQ_init + "," + FIFO_init);
		System.out.println("process_num: " + process_num + " /ready[0] ��:" + ready[0] + " /ready[1] ��: " + ready[1]
				+ " /ready[2] ��: " + ready[2] + " /ready[3] ��: " + ready[3] + " /ready[4] ��: " + ready[4]);
		System.out.println("ready[5] ��:" + ready[5] + " /ready[6] ��: " + ready[6] + " /ready[7] ��: " + ready[7]
				+ " /ready[8] ��: " + ready[8] + " /ready[9] ��: " + ready[9]);
		System.out.println("process_burst[0] ��:" + process_burst[0] + " /process_burst[1] ��: " + process_burst[1]
				+ " /process_burst[2] ��: " + process_burst[2] + " /process_burst[3] ��: " + process_burst[3]
				+ " /process_burst[4] ��: " + process_burst[4]);
		System.out.println("process_burst[5] ��:" + process_burst[5] + " /process_burst[6] ��: " + process_burst[6]
				+ " /process_burst[7] ��: " + process_burst[7] + " /process_burst[8] ��: " + process_burst[8]
				+ " /process_burst[9] ��: " + process_burst[9]);
		// ���߿� �����==============================
	}

	public void init() {// �ʱ�ȭ
		process_num = (int) (Math.random() * 10) + 1;// ������ ���μ��� ����(1~10)
		process_burst = new int[10];
		process_arrival = new int[10];
		priority = new int[10];
		ready = new int[10];
		processes_gen = 0; // ���μ��� ������ ����
		processes_gen2 = 0; // ���μ����� ���� �����ƴ��� ��
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
	public int[] RR(int[] a, int num, int quantum) {// ready�� �ִ� process, quantum��
		job_RR++;// RR�� ����� Ƚ��
		int ready[] = new int[10];
		int num_check = 0;
		ready = a;
		for (int i = 0; i < 10; i++) {
			if (a[i] > quantum) {
				ready[i] = a[i] - quantum;
				context_switch += 1; // ���� ������
				execution_time += quantum; // ���� ������

			} else {
				ready[i] = 0;
				num_check++;
			}
		}
		System.out.println("num_check = " + num_check);
		if (num_check == 10) {// ��� ���μ����� ����Ǹ�
			notReady = true;
		}
		processes_com += num - (10 - num_check);// ����� process ���� = ���� ����� process+(���� ���� process-(10-ready�� 0�ΰ���)
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
				num_check++;// burst time�� 0�� ���μ����� ����
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

		if (num_check == 10) {// ��� ���μ����� ����Ǹ�
			notReady = true;
		} else {
			processes_com += 1; // ���μ����� �ϳ����� �����ű� ������
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
			if(ready[i]!=0 &&arrival[i]<low_arri) {//burst time�� 0�� �ƴϸ鼭 ��� �ð��� ���� ���� ��
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
			System.out.println("�����Ͻðڽ��ϱ�? (1-yes) : ");
			int terminated = scanner.nextInt();
			if (terminated == 1) {
				break;
			}
		}

	}
}
