/** Screen for Password Change 
 * 
 * @author Chris Peng
 * 
 */
package com.pacman.rendering;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;

import javax.swing.*;

import com.pacman.main.Game;
import com.pacman.playermanagement.ProfileManager;
import com.pacman.rendering.Screen;

@SuppressWarnings("serial")
public class PassScreen extends Screen implements ActionListener {
	final JTextField	text1, text2;
	JLabel				label1, label2;
	JButton				SUBMIT, BACK;
	JPanel				panel;

	/** Sets up layout for password screen
	 * 
	 * @param game
	 */
	public PassScreen(Game game) {
		super(game);
		setBackground(Color.LIGHT_GRAY);
		label1 = new JLabel();
		label1.setText("New Password:");
		text1 = new JPasswordField(15);

		label2 = new JLabel();
		label2.setText("Confirm Password:");
		text2 = new JPasswordField(15);

		SUBMIT = new JButton("SUBMIT");
		BACK = new JButton("Back");
		setLayout(new GridBagLayout());
		panel = new JPanel(new GridLayout(3, 1));
		panel.add(label1);
		panel.add(text1);
		panel.add(label2);
		panel.add(text2);
		panel.add(BACK);
		panel.add(SUBMIT);

		add(panel, new GridBagConstraints());
		SUBMIT.addActionListener(this);
		BACK.addActionListener(this);

		// TODO Auto-generated constructor stub
		//m = new Menu(play);
	}

	/** Renders Screen (Unused)
	 * 
	 * 	
	 */
	@Override
	protected void render(Graphics2D g2d) {}

	/** Updates Time (Unused)
	 * 
	 * 	
	 */
	@Override
	protected void update(float deltaTime) {}

	/** Tracks Key (Unused)
	 * 
	 * 	
	 */
	@Override
	protected void keyRelease(KeyEvent e) {
		// TODO Auto-generated method stub

	}

	/** Tracks Key press (Unused)
	 * 
	 * 	
	 */
	@Override
	protected void keyPress(KeyEvent e) {
		// TODO Auto-generated method stub

	}

	/** Action Performer-- Changes screen and checks logic
	 *
	 * Checks input fields and reponds
	 * 	
	 */
	@Override
	public void actionPerformed(ActionEvent e) {

		String value1 = text1.getText();
		String value2 = text2.getText();
		String id = ((JButton) e.getSource()).getText();
		if (id.equals("SUBMIT")) {
			if (value1.equals(value2)) {
				ProfileManager.changePass(value1);
				ProfileManager.updateProfile();
				ProfileManager.printProfile();
				changeScreen(new ProfileScreen(game));
				JOptionPane.showMessageDialog(this, "Password Successfully Changed");
			} else {
				JOptionPane.showMessageDialog(this, "Passwords do not match!", "Error", JOptionPane.ERROR_MESSAGE);
			}
		}
		if (id.equals("Back")) {
			changeScreen(new ProfileScreen(game));
		}
	}
}
