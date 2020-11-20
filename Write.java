import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

class Write {
	//name�� 0�̸� ��ũ ���, 0�� �ƴϸ� ��� ���
	public void write(String log, int name) {
		try {
			String Path;//���ϰ��
			if(name == 0) {
				Path = "C:\\Users\\�ڼ���\\Desktop\\log\\Link.txt";//��ũ ���
			}
			else {
				Path =  String.format("C:\\Users\\�ڼ���\\Desktop\\log\\Node" + name + ".txt");//��� ���
			}
			
			BufferedWriter write = new BufferedWriter(new FileWriter(Path, true));

			write.write(log);
			write.close();

		} catch (IOException e) {
			System.out.println("���� ���� error");
		}
	}
	
	// �ð� ����Ʈ ���ִ� �Լ�
	public void Time(int t, int name, String log) {
		int minute = (int) (t / 60000);
		int second = (int) ((t - minute*60000) / 1000);
		int msecond = t % 1000;

		String finalLog = String.format("%02d:%02d:%03d ", minute, second, msecond) + log + "\n";// �α� �ð�
		
		
		write(finalLog, name);// �α׿� ������ ����̸�
	}
}

