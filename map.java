import java.util.Queue;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.PriorityQueue;
import java.util.Scanner;
import java.util.StringTokenizer;

public class map {

	public static void main(String[] args) {

		Scanner scanner = new Scanner(System.in);
		int line_num = 1;// ���Ͽ��� �� ��° ������ (���� �ҷ����⿡�� ���)
		Graph g = new Graph(); // �׷����� ���� ���� ����ġ�� ������
		double weight[] = new double[10001]; // ��忡 �´� ����ġ�� ���� �����ϴ� �迭 (����ġ�� ����� ������ŭ) �� 1�� ���
		                                     //weight[1] = ������ ��尡 1��
											 // ����� ����ġ�� ��
		Path p[] = new Path[10001]; // ��� ������ �迭, p[1]�̸� ��� 1�� �������� �Ǵ� ���
		                            //��ΰ� 3���̸鼭 p[1]�̸� path[2]�� ���1�� �����.
									// (��尳����ŭ �ʿ�)
		// ===========================================================================bfs�˰��򿡸� �ʿ��� �͵�
		PriorityQueue<Integer> q1 = new PriorityQueue<Integer>();
		PriorityQueue<Integer> q2 = new PriorityQueue<Integer>();
		int path_ok[] = new int[10001];// ��ο� �߰��Ǿ����� �Ǵ�
		int q1In[] = new int[10001];// q1�� ����ִ��� �Ǵ�
		int q2In[] = new int[10001];// q2�� ����ִ��� �Ǵ�

		// ===========================================================================
		try {
			// ==================================================���� �ҷ��� graph�� �����Ű��
			double a[] = new double[3];
			File file = new File("mapss.txt");// ���Ϻҷ�����
			FileReader filereader = new FileReader(file);
			BufferedReader bufReader = new BufferedReader(filereader);// ���ۿ� �ֱ�

			while (line_num != 5001) { // ���Ͽ� 5000�� ����
				String s = bufReader.readLine();// 1�� �ҷ�����
				int i = 0;
				StringTokenizer token = new StringTokenizer(s);// ��ū���� �ڸ���
				while (i != 3) {
					a[i] = Double.parseDouble(token.nextToken());// 3���� ������
					i++;
				}

				g.addGraph((int) a[0], (int) a[1], a[2]); // �ڸ��� Graph�� ����
				line_num++;// ������ �ҷ�����
			}
			// =====================================================================
			int alg = 0;
			while (alg != 3) {

				for (int i = 0; 10001 > i; i++) {
					weight[i] = 999; // ��� ����� ó�� ����ġ�� 999�� ����
				}
				for (int i = 0; 10001 > i; i++) {// ������������ 0, ���������� 1
					path_ok[i] = 0;// ������������ 0, ���������� 1
					q2In[i] = 0;// �� ��������� 0, ��������� 1
					q1In[i] = 0;// �� ��������� 0, ��������� 1
				}

				System.out.println("====================================");
				System.out.println("SSSP�˰������� ��½� 1�Է� ");
				System.out.println("BFS�˰������� ��½� 2�Է�");
				System.out.print("����� 3�Է� -> ");
				alg = scanner.nextInt();// ���� �˰��� ����Ұ��� �Է�

				if (alg == 1) {// SSSP�˰��� �̿�
					// ==========================================
					System.out.println("====================================");
					System.out.println("<single source shortest path �˰���>");
					System.out.print("���۳�带 �Է��Ͻÿ�.");
					int st = scanner.nextInt();// ���� ���
					System.out.print("�� ��带 �Է��Ͻÿ�.");
					int fi = scanner.nextInt();// �� ���

					// =============================== ��峢�� ����� ���� ã�� weight�� �����Ű�鼭 ����� ã��
					weight[st] = 0;// ù ���� ����ġ�� 0
					p[st] = new Path(); // ��� ����
					p[st].setPath(st, 0); // ù ��° ��ο� st ����

					while (true) {// ����带 ã�� ������
						int next = 0;// �Լ����� ������ ���� ���
						int connect = 0;// ������ ���
						for (int i = 1; i < 10001; i++) {//����� ������ŭ ����
							next = g.nextNode(st, i);// ���� ��带 ������

							if (next != 0) {// ������ ��尡 ������ ��
								connect = next; // connect�� ������ ��� ����
								if (weight[connect] == 999) {// connect�� ó������ ����� ��
									p[connect] = new Path();// connect��尡 ���� �� ��� ����
								}

								if (connect != 0 && weight[connect] != 1000) {// st�� ����� ���� ������ connect�� 0�� �ƴ�,
																			  // ��η� ������ ����
																			  // ����ġ�� 1000���� �����

									if (weight[connect] > weight[st] + g.getWeight(st, connect)) {// ���� weight[connect]��
																								  // �����
																						   		  // ����ġ���� ������
										weight[connect] = weight[st] + g.getWeight(st, connect);// ����ġ�� ���� ����

										int j = 0;// �� ��° �������
										while (true) {// ��� ����
											if (p[st].getPath(j) != 0) {// st�� j��° �迭�� ��ΰ� ����Ǿ� ������
												p[connect].setPath(p[st].getPath(j), j);// st�� j��° ��ο� ����Ǿ��ִ� ��带
																						// connect�� j��° ��ο� ����
												j++;
											} else {
												p[connect].setPath(connect, j);// ������ ��ι迭�� connect�� ����
												break;
											}
										}
									}
								}
							}
						}

						weight[st] = 1000; // ��η� ��� ���� ����ġ�� 1000���� ���� ������ �����

						for (int i = 0; 10001 > i; i++) {// ��� ��带 ������ ������ ���� �� ����ġ�� ���� ���� ���� ���� ����
							if (weight[st] >= weight[i]) {
								st = i;
							}
						}
						if (weight[st] == 999) {// ������� �ʾ� ����ġ�� 999�� ��尡 ���� ���� ����ġ�� �� ���� �Ұ���
							System.out.println("���� �Ұ���");
							break;
						}
						if (st == fi) {// ����Ǵٰ� ���������� ������ ������ �Ǹ�
							System.out.print("���� ���:");
							int j = 0;//�߰��Ǵ� ����� ����
							while (true) {// ��� ���
								if (p[fi].getPath(j) != 0) {
									System.out.print(p[fi].getPath(j) + "->");
									j++;
								} else {
									System.out.println("��� ��!");
									j--;
									break;
								}
							}
							double wsum = j - weight[fi];// ����ġ�� ��
							System.out.println("����ġ�� ��: " + wsum); // ����ġ�� ���� ���

							break;
						}
					}

				}
				// ==================================================================
				if (alg == 2) {// BFS�˰��� �̿�
					System.out.println("====================================");
					System.out.println("<BFS �˰���>");
					System.out.print("���۳�带 �Է��Ͻÿ�.");
					int st = scanner.nextInt();// ���� ���
					System.out.print("�� ��带 �Է��Ͻÿ�.");
					int fi = scanner.nextInt();// �� ���

					// ==============================================================
					q1.offer(st);// q1�� st�� �������
					weight[st] = 0;// st�� ����ġ�� ���� 0
					q1In[st] = 1;// q1�� st�� ��
					p[st] = new Path(); // st�� ��� ����
					p[st].setPath(st, 0); // st����� ù ��° ��ο� st ����

					while (q1.isEmpty() == false || q2.isEmpty() == false) {// q1�� q2 ��� �� ��尡 ���� ������

						// ===========================================================
						// q1�� �������鼭 q2�� ��� ����ִ� ����
						while (q1.isEmpty() != true) {//q1�� �ִ� ���� ������ ������
							int now_node = q1.poll();//q1���� ���� ��带 ������ ��
							path_ok[now_node] = 1;//��ο� ������ �ǹ���
							for (int i = 0; i < 10001; i++) {
								int next_node = g.nextNode(now_node, i);//���� ���� ����� ��� next_node�� ����
								if (next_node != 0 && path_ok[next_node] == 0 && q1In[next_node] == 0) {//���� ���� ����� ��尡 �ְ�,
																										//��ο� �� ���� ������
																										//q1�� �� ���� ���� ��
									double now_weight = weight[now_node] + g.getWeight(now_node, next_node);//now_node�� next_node���� ����ġ��
																											//now_node��  ����ġ�� �հ� ����
																											//next_node�� ����ġ�� �տ� ������
									if (weight[next_node] > now_weight) {//���� ����Ǿ��ִ� next_node ����ġ�� �պ��� ��� ���� next_node
																		 //����ġ�� ���� �� ������
										weight[next_node] = now_weight;//����ġ�� ���� ���� ������ �ٽ� ����
										if (q2In[next_node] == 0) {//q2�� �� ���� �� ���� ���� ��
											q2.offer(next_node);//q2�� ����Ǵ� ��带 �������
											q2In[next_node] = 1;//q2�� ������ �ǹ���
											p[next_node] = new Path();//���ο� ��� ����
										}
										int j = 0;//j��° ���
										while (true) {//��� ����
											if (p[now_node].getPath(j) != 0) {//now_node�� ��� �迭�� ��ΰ� ����Ǿ� ���� ������
												p[next_node].setPath(p[now_node].getPath(j), j);//connect�� ��ο� j��° ��ο�
																								//st�� j��° ��ο� ����Ǿ��ִ� 
												                                                //��带 ����
												j++;
											} else {
												p[next_node].setPath(next_node, j);
												break;
											}
										}
									}
								}
							}
						}
						// ==================================================================
						//q2�� �������鼭 q1�� ��� ����ִ� ����
						while (q2.isEmpty() != true) {// q2�� �ִ� ���� ������ ������
							int now_node = q2.poll();// ���� ��带 ������ ��
							path_ok[now_node] = 1;
							for (int i = 0; i < 10001; i++) {
								int next_node = g.nextNode(now_node, i);// ���� ���� ����� ��� next_node�� ����
								if (next_node != 0 && path_ok[next_node] == 0 && q2In[next_node] == 0) {//���� ���� ����� ��尡 �ְ�,
																										//��ο� �� ���� ������
																										//q2�� �� ���� ���� ��

									double now_weight = weight[now_node] + g.getWeight(now_node, next_node);//now_node�� next_node���� ����ġ��
																											//now_node��  ����ġ�� �հ� ����
																								     		//next_node�� ����ġ�� �տ� ������
									if (weight[next_node] > now_weight) {// ���� ����Ǿ��ִ� ����ġ�� �պ��� ���� ����� ����ġ�� ���� �� ������
										weight[next_node] = now_weight;// ����ġ�� ���� ���� ������ �ٽ� ����
										if (q1In[next_node] == 0) {
											q1.offer(next_node);// q2�� ����Ǵ� ��带 �������
											q1In[next_node] = 1;
											p[next_node] = new Path();

										}
										int j = 0;
										while (true) {// ��� ����
											if (p[now_node].getPath(j) != 0) {// now_node�� ��� �迭�� ��ΰ� ����Ǿ� ���� ������
												p[next_node].setPath(p[now_node].getPath(j), j);// connect�� ��ο� j��° ��ο�
																								// st�� j��° ��ο�
																								// ����Ǿ��ִ� ��带 ����
												j++;
											} else {
												p[next_node].setPath(next_node, j);
												break;
											}
										}
									}
								}
							}
						}
						// ==================================================================
					}
					if (weight[fi] != 999) {
						int j = 0;
						System.out.print("���� ���: ");
						while (true) {// ���� ���

							if (p[fi].getPath(j) != 0) {
								System.out.print(p[fi].getPath(j) + "->");
								j++;
							} else {
								System.out.println("��� ��!");
								j--;
								break;
							}
						}
						double wsum = j - weight[fi];// ����ġ�� ��
						System.out.println("����ġ�� ��: " + wsum); //����� ����-weight[fi]
					} else {
						System.out.println("���� �Ұ���");
					}
				}
			}
			System.out.println("�����մϴ�...");
		} catch (FileNotFoundException e) {
		} catch (IOException e) {
			System.out.println(e);
		}
	}
}

class Graph {// ���ͽ�Ʈ�� �˰��� ����� ��
	double distance[][];

	public Graph() {
		distance = new double[10001][10001]; // a�� b�� ��带 ����[10001][10001]
	}

	public void addGraph(int a, int b, double weight) {// ����ġ �����ϴ� �Լ�
		distance[a][b] = 1 - weight;
		distance[b][a] = 1 - weight;
	}

	public double getWeight(int a, int b) {// ����ġ �ҷ����� �Լ�
		return distance[a][b];
	}

	public int nextNode(int a, int b) {
		int c = 0; // nextnode�� ���� ��, 0�� ������ �Ǿ� �����ϱ� 0�� ������ ���� �Ұ��� ���!

		if (distance[a][b] != 0) {
			c = b;
		}

		return c;
	}
}

class Path {// ��� ����
	int path[];

	public Path() {
		path = new int[10000];
	}

	public int getPath(int i) {// ���� 1->3->7 ��ζ�� ��� 1�� path[0]�� 1�� ����, ��� 3�� ��� 1�� getPath(0)�� ����� ���3��
								// path[0]�� 1�� �����ϰ�, path[1]�� 3�� ����, ��� 7�� ��� 3�� getPath(0), getPath(1) �̿��ؼ�
								// path[0], path[1] �����ϰ� path[2]�� �ڱⲨ ����
		return path[i];
	}

	public void setPath(int node, int i) {
		path[i] = node;
	}
}
