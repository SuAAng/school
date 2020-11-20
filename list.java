import java.util.Scanner;
import java.util.StringTokenizer;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

class ListNode{
	String data;
	ListNode Rlink;
	ListNode Llink;
	
	public ListNode(String data) {
		this.data = data;
		this.Rlink = null;
		this.Llink = null;
	}
}

class LinkedList{
	ListNode head = new ListNode(null);//�����
	
	public ListNode create_node (String data) {
		ListNode new_node = new ListNode(data);
		
		return new_node;
	}

	public void insert_node (String data) {
		ListNode temp_node = head;//�ӽ÷� ����� ��
		ListNode new_node = create_node(data);
		if (head.data == null) {//����Ʈ�� �ƹ��͵� ���� ��
			head = new_node;
		}
		
		else {
			while (true) {
				if (temp_node.data.compareTo(new_node.data) < 0) {//���� ��庸�� �� ��尡 ũ�� ������ ��ũ��

					if (temp_node.Rlink == null) {
						temp_node.Rlink = new_node;
						break; //�� ��� ���� �����ְ� �ݺ��� ����
					}
					temp_node = temp_node.Rlink;
				}
				else if (temp_node.data.compareTo(new_node.data) > 0) {//���� ��庸�� �� ��尡 ũ�� ���� ��ũ��
					if (temp_node.Llink == null) {
						temp_node.Llink = new_node;
						break; //�� ��� ���� �����ְ� �ݺ��� ����
					}
					temp_node = temp_node.Llink;
				}
				else {//�̹� ����Ǿ� �ִٸ� ���� ����
					break;
				}
			}
		}	
	}
}

public class list {
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		try {

			FileReader fr = new FileReader(new File("test.txt"));

			char[] buffer = new char[100];
			String word = "";
			
			while(fr.read(buffer) != -1){
			word = word + String.valueOf(buffer);
			}
			
		LinkedList link = new LinkedList();
		
		String [] s;//�ܾ� ���� ����
		StringTokenizer tok = new StringTokenizer(word," \n");//��ū
		String search;//��ġ�� �ܾ�
		int i = 0, k = 0;

		int n = tok.countTokens();//token ����
		
		s = new String[n];
		
		for(i = 0; i < n; i++) {
			s[i]= tok.nextToken();
		}

		//����Ʈ �ֱ�
		link.insert_node (s[0]); //Ʈ���� �� ���� �־���.
		
		k = 1;
		while (k < n) {
			link.insert_node (s[k]);
			k++;
		}
		//����� �ܾ� ã��
		while(true){
			ListNode nlist = link.head;//�˻��� �� ���� ���� ����Ʈ
			System.out.print("�˻��� �ܾ �Է��Ͻÿ�(0�Է� �� ����)>> ");
			search = scanner.next();
			if(search.compareTo("0") == 0) {
				System.out.print("����");
				break;
			}
			while (true) {
				if (nlist == null) {
					System.out.println(search + "��/�� ������ �������� �ʽ��ϴ�.");
					break;
				}
				else if (nlist.data.compareTo(search) == 0) {
					System.out.println(search + "��/�� ������ �����մϴ�.");
					break;
				}
				else if (nlist.data.compareTo(search) < 0) {
					nlist = nlist.Rlink;
				}
				else if (nlist.data.compareTo(search) > 0) {
					nlist = nlist.Llink;
				}
			}
		}
		} catch (FileNotFoundException e) {
			e.printStackTrace();
			} catch (IOException e) {
			e.printStackTrace();
			}
	}
		
}

	
