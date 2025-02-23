package swing;

import javax.swing.*;

import java.awt.event.*;

/// @brief Classe principale de l'application.
public class Main extends JFrame {
    private static final long serialVersionUID = 1L;

    static Client client;

    static int WIDTH = 40;
    static int HEIGHT = 15;
    static JTextArea text = new JTextArea(HEIGHT, WIDTH);
    static JTextField input = new JTextField(WIDTH);

    public Main() {
        JScrollPane scrollPane = new JScrollPane(text);
        text.setLineWrap(true);
        text.setWrapStyleWord(true);

        // Ensemble des boutons de la barre d'outils et du menu.
        Object[] buttons = new Object[] {
                new Button("Jouer", (event) -> send("play", input.getText())),
                new JSeparator(),
                new Button("Lister les media", (event) -> send("listmedia")),
                new Button("Chercher un media", (event) -> send("findmedia", input.getText())),
                new Button("Supprimer un media", (event) -> send("deletemedia", input.getText())),
                new JSeparator(),
                new Button("Lister les groupes", (event) -> send("listgroup")),
                new Button("Chercher un groupe", (event) -> send("findgroup", input.getText())),
                new Button("Supprimer un group", (event) -> send("deletegroup", input.getText())),
                new JSeparator(),
                new Button("Sauvegarder", (event) -> send("save", input.getText())),
                new Button("Charger", (event) -> send("load", input.getText())),
                new JSeparator(),
                new Button("Quitter", (event) -> System.exit(0))
        };

        JToolBar toolBar = new JToolBar();

        JMenuBar menuBar = new JMenuBar();
        JMenu menu = new JMenu("Action");
        menuBar.add(menu);

        // Ajout des boutons à la barre d'outils et au menu.
        for (Object button : buttons) {
            if (button instanceof JSeparator) {
                toolBar.addSeparator();
                menu.addSeparator();
                continue;
            }

            toolBar.add((Button) button);
            menu.add(new JMenuItem((Button) button));
        }

        setJMenuBar(menuBar);
        getContentPane().add(scrollPane, "Center");
        getContentPane().add(toolBar, "North");
        getContentPane().add(input, "South");

        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        setTitle("Télécommande");
        pack();
        setVisible(true);
    }

    /// @brief Envoie une requête au serveur et affiche la réponse.
    private void send(String request, String... args) {
        for (String arg : args) {
            request += " " + arg;
        }
        String response = client.send(request);
        response = response.replace(";", "\n");

        String separtor = String.format("\n--- %s ---\n", request);
        text.append(separtor);

        text.append(response);
    }

    /// @brief Point d'entrée du programme.
    public static void main(String argv[]) {
        try {
            client = new Client("localhost", 3331);
        } catch (Exception e) {
            System.err.println("Client: Couldn't connect to localhost:3331");
            System.exit(1);
        }

        new Main();
    }

}

/// @brief Class pour un Button. Peut être utilisé pour les boutons de la barre
/// d'outils et du menu.
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
