import java.util.Scanner;
import java.util.StringTokenizer;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
public class array {
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		
		
		try {

			FileReader fr = new FileReader(new File("test.txt"));
			
			char[] buffer = new char[100];
			String word = "";
			
			while(fr.read(buffer) != -1){
			word = word + String.valueOf(buffer);
			}


			String [] s;//�ܾ� ���� ����
			StringTokenizer tok = new StringTokenizer (word," \n");
			String [] tree;//Ʈ�������� �ܾ� ����
			String search;//��ġ�� �ܾ�
			int i = 0;
			int k = 0;
			int cmp;//2�� ��
		
			int n = tok.countTokens();//token ����
			
			s = new String[n];
			tree = new String[1000000];
			
			for(i = 0; i<n; i++) {
				s[i]= tok.nextToken();
			}

			//Ʈ�� ����
			k = 0; i = 1;
			while (k < n) {

				if (tree[i] == null) {//tree�� ����� ������ ä���ֱ�
					tree[i] = s[k];
					k++;
					i = 1;//�ְ��� �ٽ� Ʈ�� 1���� ����	
				}
				else {
					cmp = tree[i].compareTo(s[k]);
					if (cmp < 0)//s[k]�� �� �ڿ� ������
					{
						i = (i * 2) + 1;
					
					}
					else if (cmp > 0) //s[k]�� �� �տ� ������
					{
						i = i * 2;
					
					}
					else//�̹� ����� �ܾ��� ��
					{
						i = 1;// �ٽ� Ʈ��1���� ����
						k++;
					}
				}	
			}
		
			//������� �Ϻ�
			//Ʈ���� ����� �ܾ� ã��
			System.out.println("dkssud");
			while(true) {
				System.out.print("�˻��� �ܾ �Է��Ͻÿ�(0�Է� �� ����)>> ");
				search = scanner.next();
				if(search.compareTo("0") == 0) {
					System.out.print("����");
					break;
				}	
				i = 1;
				while(true) {
					if (tree[i] == null) {
						System.out.println(search + "��/�� ������ ���������ʽ��ϴ�.");
						break;
					}	
					else if (tree[i].compareTo(search) == 0) {
						System.out.println(search + "��/�� ������ �����մϴ�.");
						break;
					}
					else if (tree[i].compareTo(search) < 0) {
						i = (i * 2) + 1;
					}	
					else if (tree[i].compareTo(search) > 0) {
						i = i * 2;
					}	
			
				}
			}
			System.out.println(word);
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
		e.printStackTrace();
		}
	}

}

