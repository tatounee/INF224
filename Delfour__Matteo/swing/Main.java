package swing;

import javax.swing.*;
import java.awt.event.*;

public class Main extends JFrame {
    // JScrollPane scrollPane;
    // JTextArea text;

    // JMenuBar menuBar;
    // JToolBar toolBar;
    // Button button0;
    // Button button1;
    // Button button2;

    public Main() {
        JTextArea text = new JTextArea(10, 30);
        text.setLineWrap(true);
        text.setWrapStyleWord(true);
        JScrollPane scrollPane = new JScrollPane(text);

        Button button0 = new Button("Click 0", (event) -> text.append("Button 0 clicked\n"));
        Button button1 = new Button("Click 1", (event) -> text.append("Button 1 clicked\n"));
        Button button2 = new Button("Quit", (event) -> System.exit(0));

        JToolBar toolBar = new JToolBar();
        toolBar.add(button0);
        toolBar.add(button1);
        toolBar.add(button2);

        JMenu menu = new JMenu("Action");
        menu.add(new JMenuItem(button0));
        menu.add(new JMenuItem(button1));
        menu.add(new JMenuItem(button2));
        JMenuBar menuBar = new JMenuBar();
        menuBar.add(menu);

        setJMenuBar(menuBar);
        getContentPane().add(scrollPane, "Center");
        getContentPane().add(toolBar, "South");

        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        setTitle("Télécommande");
        pack();
        setVisible(true);
    }

    public static void main(String argv[]) {
        Main toplevel = new Main();
    }

}

class Button extends AbstractAction {
    ActionListener action;

    public Button(String name, ActionListener actionListener) {
        super(name);
        action = actionListener;
    }

    public void actionPerformed(ActionEvent e) {
        action.actionPerformed(e);
    }
}
