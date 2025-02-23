package swing;

import javax.swing.*;

public class Main extends JFrame {
    JScrollPane scrollPane;
    JTextArea text;

    JPanel buttonPanel;
    JButton button0;
    JButton button1;
    JButton button2;

    public static void main(String argv[]) {
        Main toplevel = new Main();
    }

    public Main() {
        text = new JTextArea(10, 30);
        text.setLineWrap(true);
        text.setWrapStyleWord(true);
        scrollPane = new JScrollPane(text);

        buttonPanel = new JPanel();
        button0 = new JButton("Click 0");
        button1 = new JButton("Click 1");
        button2 = new JButton("Quit");

        button0.addActionListener((event) -> text.append("Button 0 clicked\n"));
        button1.addActionListener((event) -> text.append("Button 1 clicked\n"));
        button2.addActionListener((event) -> System.exit(0));

        buttonPanel.add(button0);
        buttonPanel.add(button1);
        buttonPanel.add(button2);

        getContentPane().add(scrollPane, "Center");
        getContentPane().add(buttonPanel, "South");

        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        setTitle("Télécommande");
        pack();
        setVisible(true);
    }
}