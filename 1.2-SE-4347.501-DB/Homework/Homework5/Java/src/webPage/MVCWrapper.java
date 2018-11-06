package webPage;

// this file wraps the Model View Controller object instantiation for main to use

import java.awt.Container;
import java.awt.Insets;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFormattedTextField;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextField;

import java.awt.event.*;

import javax.swing.*;

import java.awt.*;
import java.awt.event.*;

import javax.swing.BorderFactory;
import javax.swing.border.Border;

import java.awt.BorderLayout;
import java.awt.Component;

import static javax.swing.GroupLayout.Alignment.*;
import static javax.swing.GroupLayout.*;

public class MVCWrapper extends JFrame implements ActionListener{
	
	// attributes
	static final long serialVersionUID = 0L;
	// each JFrame object must be static, so controller and view can access them
	// model is completely unaware that these exist
	static JButton factButton = new JButton("Display New Fact");
	static String factString = new String();
	static JTextField factField = new JTextField("Blank starting Text");
	// these are the actual objects for the Model View Controller design pattern
	static Model myModel;
	static View myView;
	static Controller myController;
	
	
	// main method
	public static void main(String[] args) {
		System.out.println("\nMain started.");
		System.out.println("\nModel View Controller Wrapper will now instantiate GUI.");
		myModel = new Model();
		myView  = new View();
		myController = new Controller();
		
		myController.setView(myView);
		myController.setModel(myModel);
		
        //Schedule a job for the event-dispatching thread:
        //creating and showing this application's GUI.
        javax.swing.SwingUtilities.invokeLater(new Runnable() {
            public void run() {
            	MVCWrapper myWrapper = new MVCWrapper();
            }
        });		
	   
	} 	
	
	// default constructor
	// creates the frame with all wrapper panels
	MVCWrapper(){
		
		//Create and set up the frame
		JFrame frame = new JFrame("Facts GUI Frame");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	
		//set size, display and layout of the frame
		Insets insets = frame.getInsets();
		frame.setSize(440,550);
		frame.setVisible(true);
		frame.setLayout(new BorderLayout());
		
		// set options for items that will go in the frame
		factField.setEditable(true);
		// only add actionListener to the button
		factButton.addActionListener(this);
		
		// create a wrapper panel to hold all the things necessary
		JPanel factWrapperPanel = new JPanel(new BorderLayout());
		factWrapperPanel.setPreferredSize(new Dimension(600,200));
		
		// create wrapper panel with a button in the center
		JPanel factButtonWrapperPanel = new JPanel (new BorderLayout());
		factButtonWrapperPanel.setPreferredSize(new Dimension(580, 180));
		factButtonWrapperPanel.add(factButton, BorderLayout.CENTER);
	
		// create wrapper panel with a field in the center
		JPanel factFieldWrapperPanel = new JPanel (new BorderLayout());
		factFieldWrapperPanel.setPreferredSize(new Dimension(580, 180));
		factFieldWrapperPanel.add(factField, BorderLayout.CENTER);
		
		// add wrapper panels to main wrapper panel
		// then add the main wrapper to the frame
		frame.add(factButtonWrapperPanel, BorderLayout.NORTH);
		frame.add(factFieldWrapperPanel, BorderLayout.SOUTH);
		frame.add(factWrapperPanel, BorderLayout.CENTER);
		
		// pack the frame for tightness
		frame.pack();
	}
	
	// methods
	
	// action Performed 
	// this handles all mouse and keyboard clicks for the GUI
	// this method CAN NOT be instantiated
	// this means in cannot exist in any class that is actually used to make objects
	// This is one of the purposes of the MVCWrapper class file
	// this class is NOT instantiated, it holds the GUI and implements the actionPerformed method
	// The only purpose is to hold this method which pairs with the JFrame objects above
	public void actionPerformed  (ActionEvent e){

		// display new fact
		if(e.getSource() == factButton)
		{
		System.out.println("\nListener decteded fact button click.");
		
		// access data as follows
		// use controller
		// to get data from model
		// pipe back into controller
		// use controller
		// to pipe data into view
		// the getRandomFact in the Controller class does all of this
		myController.getRandomnFact();
		}
	}
   

    
}
