package com.pacman.rendering;

import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;

import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JPasswordField;
import javax.swing.JTextField;

import com.pacman.main.Game;
import com.pacman.playermanagement.ProfileManager;

@SuppressWarnings("serial")
public class LoginScreen extends Screen implements ActionListener {
	final JTextField	text1, text2;
	JLabel				label0, label1, label2;
	JButton				SUBMIT, NEWACC, CONTINUE;
	JPanel				panel;

	public LoginScreen(Game game) {
		super(game);
		setBackground(Color.LIGHT_GRAY);
		label0 = new JLabel();
		label0.setText("Logged in as: " + game.getUser());
		CONTINUE = new JButton("Continue");

		if (game.getUser() != "Guest") {
			System.out.print(game.getUser());
		} else {
			System.out.print("Guest");
		}

		label1 = new JLabel();
		label1.setText("Username:");
		text1 = new JTextField(15);

		label2 = new JLabel();
		label2.setText("Password:");
		text2 = new JPasswordField(15);

		SUBMIT = new JButton("SUBMIT");
		NEWACC = new JButton("Create New Account");
		setLayout(new GridBagLayout());
		panel = new JPanel(new GridLayout(4, 1));
		panel.add(label0);
		panel.add(CONTINUE);
		panel.add(label1);
		panel.add(text1);
		panel.add(label2);
		panel.add(text2);
		panel.add(SUBMIT);
		panel.add(NEWACC);
		add(panel, new GridBagConstraints());
		CONTINUE.addActionListener(this);
		SUBMIT.addActionListener(this);
		NEWACC.addActionListener(this);
		game.repaint();

		// TODO Auto-generated constructor stub
		//m = new Menu(play);
	}

	@Override
	protected void render(Graphics2D g2d) {}

	@Override
	protected void update(float deltaTime) {}

	@Override
	protected void keyRelease(KeyEvent e) {
		// TODO Auto-generated method stub

	}

	@Override
	protected void keyPress(KeyEvent e) {
		// TODO Auto-generated method stub

	}

	@Override
	public void actionPerformed(ActionEvent e) {
		String id = ((JButton) e.getSource()).getText();
		if (id.equals("SUBMIT")) {

			String value1 = text1.getText();
			String value2 = text2.getText();
			ProfileManager.findUser(value1);
			if (ProfileManager.findUser(value1) && ProfileManager.checkPass(value2)) {
				game.setUser(value1);
				changeScreen(new ProfileScreen(game));

				JOptionPane.showMessageDialog(this, "Successfully Logged in");
			} else {
				JOptionPane.showMessageDialog(this, "Incorrect login or password", "Error", JOptionPane.ERROR_MESSAGE);
			}

		}
		if (id.equals("Continue")) {
			if (game.getUser().equals("Guest")) {
				changeScreen(new MainMenuScreen(game));
			} else {
				changeScreen(new ProfileScreen(game));
			}
		}
		if (id.equals("Create New Account")) {
			String value1 = text1.getText();
			String value2 = text2.getText();
			if (ProfileManager.findUser(value1)) {
				JOptionPane.showMessageDialog(this, "Username already taken, Please choose another.", "Error", JOptionPane.ERROR_MESSAGE);
			} else {
				ProfileManager.createNewUser(value1, value2);
				game.setUser(value1);
				ProfileManager.findUser(value1);
				changeScreen(new ProfileScreen(game));
			}
		}
	}
}
