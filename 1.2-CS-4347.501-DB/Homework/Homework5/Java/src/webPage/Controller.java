package webPage;

/*MVC Notes:
https://www.tomdalling.com/blog/software-design/model-view-controller-explained/
	Summary:
	Model View and Controller work best when separated
	Model		- holds data
	View		- loads data independently of the Model
	Controller	- provides model data to view, also performs operations on the data
	
	
https://code.tutsplus.com/tutorials/mvc-for-noobs--net-10488
*/

public class Controller {
	// attributes
	protected Model model;
	protected View view;
	private static Fact ControllerFactBufferObject;
	// constructors

	// methods
	
	// addFact is not used in this implementation at this point
	// facts 
	public Fact getRandomnFact(){
		System.out.println("\nGetting Fact from Model with Controller");

		try{
			System.out.println("\nSetting static field in Model with Controller");
			ControllerFactBufferObject = Model.getRandomnFact();
			View.setFactField(ControllerFactBufferObject);
			return ControllerFactBufferObject;
		}
	    catch (Exception e)
	    {
	      System.err.println("Controller encountered exception while getting Fact to Model!");
	      System.err.println(e.getMessage());
	      return ControllerFactBufferObject;
	    }
		
	}	
	
	// setters for assembling the pieces in main Make Calendar
    public void setModel(Model m){
    	System.out.println("\nSetting Model for Controller");
    	this.model = m;
    	
    }
    public void setView(View v){
    	System.out.println("\nSetting View for Controller");
    	this.view = v;
    }
}
