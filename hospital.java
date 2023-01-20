package hospital;
//Hospital backend project
import java.util.*;

public class Hospital {
	protected Director director; // can have 1 Director.
	protected Administrator admin;
	protected Physician physician;
	protected Volunteer volunteer;
	protected Patient patient;
	protected PhysicianAdministrator physicianAdmin;
	protected ArrayList<PhysicianAdministrator> hospitalAdminList; //hospital admin list containing the physicians admins
	protected ArrayList<Physician> hospitalPhysicianList; // list of each physician in the hospital
	protected ArrayList<Patient> hospitalPatientList; // list of all patients in the hospital
	protected ArrayList<Volunteer> hospitalVolunteerList; // list of all volunteers in the hospital

	//constructor for Hospital
	public Hospital(Director director) {
		this.director = director;
		this.hospitalAdminList = new ArrayList<>();
		this.hospitalPhysicianList = new ArrayList<>();
		this.hospitalPatientList = new ArrayList<>();
		this.hospitalVolunteerList = new ArrayList<>();

	}

	//returns Director of the hospital
	protected Director getHospDirector() {
		return this.director;
	}

	// adds admin to hospital
	// each hospital can have 3 admins
	protected boolean addAdministrator(PhysicianAdministrator p) {
		if (hospitalAdminList.size() < 3)
			return hospitalAdminList.add(p);
		else
			return false;
	}

	// hires physician to hospital
	// each hospital can have 70 physicians
	// each physician can have up to 8 patients
	protected boolean hirePhysician(Physician p) {
		if (hospitalPhysicianList.size() < 70 && !(hospitalPhysicianList.contains(p))) {
			for (int i = 0; i < hospitalAdminList.size(); i++) {
				if (hospitalAdminList.get(i).type.equals(p.type) && hospitalPhysicianList.size() < 25) {
					hospitalAdminList.get(i).adminPhysicianList.add(p);
				}
			}
			return hospitalPhysicianList.add(p);
		} else
			return false;
	}

	// adds patient to hospital
	// hospital can have upto 8 patients per physician in the hospital
	// max number of patients is 500
	protected boolean admitPatient(Patient p) throws NoSpaceException {
		if (hospitalPatientList.size() < (hospitalPhysicianList.size() * 8) && !(hospitalPatientList.contains(p))) {
			hospitalPatientList.add(p);
			for (int i = 0; i < hospitalPhysicianList.size(); i++) {
				if (hospitalPhysicianList.get(i).physicianPatientList.size() < 8) {
					hospitalPhysicianList.get(i).physicianPatientList.add(p);
					p.setAssignedPhysician(hospitalPhysicianList.get(i));
					hospitalPhysicianList.get(i).patientCounter++;
					break;
				}
			}
			return true;
		}

		else if (hospitalPatientList.size() > 500 || (hospitalPatientList.size() >= (hospitalPhysicianList.size() * 8)))
			throw new NoSpaceException("");

		else
			return false;

	}

	//returns all physicians details
	protected ArrayList<Physician> extractAllPhysicianDetails() {
		return hospitalPhysicianList;
	}

	// removes physisican from hospital while un assigning volunteers and patients from him
	// and deleting the records.
	protected boolean resignPhysician(Physician p) throws NoSpecialtyException {
		if (hospitalPhysicianList.contains(p)) {
			for (int i = 0; i < p.physicianPatientList.size(); i++)
				reAdmitPateint(p.physicianPatientList.get(i));

			for (int i = 0; i < p.physicianVolunteerList.size(); i++)
				reHireVolunteer(p.physicianVolunteerList.get(i));

			p.physicianPatientList.clear();
			p.physicianVolunteerList.clear();
			p.patientCounter = 0;
			p.volunteerCounter = 0;
			return hospitalPhysicianList.remove(p);

		} else
			throw new NoSpecialtyException("");
	}

	// returns all patients details.
	protected ArrayList<Patient> extractAllPatientDetails() {
		return hospitalPatientList;
	}

	// removes patient from hospital and clears records.
	protected boolean dischargePatient(Patient p) {
		if (hospitalPatientList.contains(p)) {
			for (int i = 0; i < hospitalPhysicianList.size(); i++) {
				if (hospitalPhysicianList.get(i).physicianPatientList.contains(p)) {
					hospitalPhysicianList.get(i).physicianPatientList.remove(p);
					hospitalPatientList.remove(p);
					break;
				}
			}
			return true;
		} else
			return false;
	}
	
	// helper function for re-assigning patients once physician leaves.
	private boolean reAdmitPateint(Patient p) {
		if (hospitalPatientList.size() < (hospitalPhysicianList.size() * 8) && hospitalPatientList.contains(p)) {
			for (int i = 0; i < hospitalPhysicianList.size(); i++) {
				if (hospitalPhysicianList.get(i).physicianPatientList.size() < 8) {
					hospitalPhysicianList.get(i).physicianPatientList.add(p);
					break;
				}
			}
			return true;
		} else
			return false;
	}

	// helper function for re-assigning volunteer once physician leaves.
	private boolean reHireVolunteer(Volunteer v) {
		if (hospitalVolunteerList.size() < (hospitalPhysicianList.size() * 5) && hospitalVolunteerList.contains(v)) {
			for (int i = 0; i < hospitalPhysicianList.size(); i++) {
				if (hospitalPhysicianList.get(i).physicianVolunteerList.size() < 5) {
					hospitalPhysicianList.get(i).physicianVolunteerList.add(v);
					break;
				}
			}
			return true;
		} else
			return false;
	}

	// hires volunteer to hospital and assigns them to physicians in a "first come, first serve" style.
	protected boolean hireVolunteer(Volunteer v) {
		if (hospitalVolunteerList.size() < (hospitalPhysicianList.size() * 5) && !(hospitalVolunteerList.contains(v))) {
			hospitalVolunteerList.add(v);
			for (int i = 0; i < hospitalPhysicianList.size(); i++) {
				if (hospitalPhysicianList.get(i).physicianVolunteerList.size() < 5) {
					hospitalPhysicianList.get(i).physicianVolunteerList.add(v);
					hospitalPhysicianList.get(i).volunteerCounter++;

					break;
				}
			}
			return true;
		}

		else
			return false;

	}

	// resigns volunteer
	protected boolean resignVolunteer(Volunteer v) throws NoVolunteersException {
		if (hospitalVolunteerList.contains(v)) {
			for (int i = 0; i < hospitalPhysicianList.size(); i++) {
				if (hospitalPhysicianList.get(i).physicianVolunteerList.contains(v)) {
					hospitalPhysicianList.get(i).physicianVolunteerList.remove(v);
					hospitalVolunteerList.remove(v);
					hospitalPhysicianList.get(i).volunteerCounter--;

					break;
				}
			}
			return true;
		} else
			throw new NoVolunteersException("");
	}
	
	//returns all volunteers details
	public ArrayList<Volunteer> extractAllVolunteerDetails() {
		return hospitalVolunteerList;
	}
}

class Person {
	protected String firstName;
	protected String lastName;
	protected int age;
	protected String gender;
	protected String address;

	public Person(String firstName, String lastName, int age, String gender, String address) {
		this.firstName = firstName;
		this.lastName = lastName;
		this.age = age;
		this.gender = gender;
		this.address = address;
	}

	public String getFirstName() {
		return firstName;
	}

	public String getLastName() {
		return lastName;
	}

	public int getAge() {
		return age;
	}

	public String getGender() {
		return gender;
	}

	public String getAddress() {
		return address;
	}

	protected void setFirstName(String firstName) {
		this.firstName = firstName;
	}

	protected void setLastName(String lastName) {
		this.lastName = lastName;
	}

	protected void setAge(int age) {
		this.age = age;
	}

	protected void setGender(String gender) {
		this.gender = gender;
	}

	protected void setAddress(String address) {
		this.address = address;
	}

	public String getName() {
		return firstName + ", " + lastName;
	}

	@Override
	public String toString() {
		return "[" + firstName + ", " + lastName + ", " + age + ", " + gender + ", " + address + "]";
	}

}

class Employee extends Person {
	protected double salary = 0.0;
	protected static int employeeID = 100;
	protected static int id;

	public Employee(String firstName, String lastName, int age, String gender, String address) {
		super(firstName, lastName, age, gender, address);
		id = employeeID;
		employeeID++;
	}

	protected int getEmployeeID() {
		return id;
	}

}

class Volunteer extends Employee {

	public Volunteer(String firstName, String lastName, int age, String gender, String address) {
		super(firstName, lastName, age, gender, address);
	}

	public double getSalary() {
		return salary;
	}

	protected void setSalary(double salary) {

	}

	public int getID() {
		return employeeID;
	}

	@Override
	public String toString() {
		return "Volunteer [[" + id + ",[" + firstName + ", " + lastName + ", " + age + ", " + gender + ", " + address
				+ "]]]";
	}

}

class SalariedEmployee extends Employee {
	protected double salary;
	protected String type;

	public SalariedEmployee(String firstName, String lastName, int age, String gender, String address) {
		super(firstName, lastName, age, gender, address);

	}

	public double getSalary() {
		return salary;
	}

	public void setSalary(double salary) {
		this.salary = salary;
	}

	protected void setAdminSpecialtyType(String type) {
		this.type = type;
	}

	protected String getAdminSpecialtyType() {
		return type;
	}

}

class Administrator extends SalariedEmployee {
	public Administrator(String firstName, String lastName, int age, String gender, String address) {
		super(firstName, lastName, age, gender, address);
	}

	protected void setAdminSpecialtyType(String type) {
		if (type.equals("Immunology") || type.equals("Dermatology") || type.equals("Neurology"))
			this.type = type;
		else
			throw new IllegalArgumentException("Invaild specialty");
	}

	public String toString() {
		return "Administrator [[[" + id + ",[" + firstName + ", " + lastName + ", " + age + ", " + gender + ", "
				+ address + "]], " + salary + "], " + type + "]";
	}

}

class Physician extends SalariedEmployee {
	protected ArrayList<Patient> physicianPatientList;
	protected ArrayList<Volunteer> physicianVolunteerList;
	protected int volunteerCounter;
	protected int patientCounter;

	public Physician(String firstName, String lastName, int age, String gender, String address) {
		super(firstName, lastName, age, gender, address);
		this.physicianPatientList = new ArrayList<>();
		this.physicianVolunteerList = new ArrayList<>();
		this.patientCounter = 0;
		this.volunteerCounter = 0;
	}

	protected void setSpecialty(String type) {
		if (type.equals("Immunology") || type.equals("Dermatology") || type.equals("Neurology"))
			this.type = type;
		else
			throw new IllegalArgumentException("Invaild specialty");
	}

	public String getSpecialty() {
		return type;
	}

	protected ArrayList<Patient> extractPatientDetail() {
		return physicianPatientList;
	}

	protected ArrayList<Volunteer> extractValunterDetail() {
		return physicianVolunteerList;
	}

	protected boolean assignVolunteer(Volunteer v) {
		if (physicianVolunteerList.size() < 5) {
			volunteerCounter++;
			return physicianVolunteerList.add(v);
		} else
			return false;
	}

	protected boolean hasMaxVolunteers() {
		if (volunteerCounter == 5)
			return true;
		else
			return false;
	}

	protected boolean hasMaximumpatient() {
		if (patientCounter == 8)
			return true;
		else
			return false;
	}

	@Override
	public String toString() {
		return "Physician [[[" + id + ",[" + firstName + ", " + lastName + ", " + age + ", " + gender + ", " + address
				+ "]], " + salary + "]]";
	}

}

class PhysicianAdministrator extends Administrator {
	protected ArrayList<Physician> adminPhysicianList;

	public PhysicianAdministrator(String firstName, String lastName, int age, String gender, String address) {
		super(firstName, lastName, age, gender, address);
		this.adminPhysicianList = new ArrayList<>();
	}

	protected ArrayList<Physician> extractPhysician() {
		return adminPhysicianList;
	}

	@Override
	public String toString() {
		return "PysicianAdministrator [[[" + id + ",[" + firstName + ", " + lastName + ", " + age + ", " + gender + ", "
				+ address + "]], " + salary + "], " + type + "]";
	}
}

class Director extends Administrator {
	protected ArrayList<PhysicianAdministrator> adminList;

	public Director(String firstName, String lastName, int age, String gender, String address) {
		super(firstName, lastName, age, gender, address);
		this.adminList = new ArrayList<>();
	}

	public boolean assignAdministrator(PhysicianAdministrator admin) {
		if (adminList.size() < 3)
			return adminList.add(admin);
		else
			return false;
	}

	public ArrayList<PhysicianAdministrator> extractPhysicianAdmins() {
		return adminList;
	}

	@Override
	public String toString() {
		return "Director [[[" + id + ",[" + firstName + ", " + lastName + ", " + age + ", " + gender + ", " + address
				+ "]], " + salary + "], " + type + "]";
	}
}

class Patient extends Person {
	protected static int PatientID = 1000;
	protected static int pID;
	protected Physician assignedPhysician;

	public Patient(String firstName, String lastName, int age, String gender, String address) {
		super(firstName, lastName, age, gender, address);
		pID = PatientID;
		PatientID++;
	}

	public int getPatientID() {
		return pID;
	}

	protected void setAssignedPhysician(Physician p) {
		this.assignedPhysician = p;
	}

	protected Physician getAssignedPhysician() {
		return assignedPhysician;
	}

	protected boolean clearPatientRecord() {
		if (assignedPhysician == null) {
			return true;
		} else
			return false;

	}

	@Override
	public String toString() {
		return "Patient " + "[" + pID + ", [" + firstName + ", " + lastName + ", " + age + ", " + gender + ", "
				+ address + "]]";
	}

}

class NoSpaceException extends Exception {
	public NoSpaceException(String errorMsg) {
		super(errorMsg);
	}
}

class NoSpecialtyException extends Exception {
	public NoSpecialtyException(String errorMsg) {
		super(errorMsg);
	}
}

class NoVolunteersException extends Exception {
	public NoVolunteersException(String errorMsg) {
		super(errorMsg);
	}
}
