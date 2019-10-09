package repository;

import domain.Vehicle;

public class VehicleRepository {
	private static final Integer MAX_CAPACITY = 100;

	private Vehicle[] vehicles;
	private int numberOfVehicles;

	public VehicleRepository() {
		this.numberOfVehicles = 0;
		vehicles = new Vehicle[100];
	}

	public void addVehicle(Vehicle newVehicle) {
		if (numberOfVehicles <= MAX_CAPACITY) {
			vehicles[numberOfVehicles] = newVehicle;
			numberOfVehicles++;
		} else {
			System.out.println("No vehicles can be added to the stock");
		}
	}

	public Vehicle getVehicleAtPosition(int position) {
		return vehicles[position];
	}

	public int getNumberOfVehicles(){
		return numberOfVehicles;
	}
}
