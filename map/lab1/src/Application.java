import domain.Vehicle;
import repository.VehicleRepository;
import utils.MileageUnit;

public class Application {
	public static void main(String[] args) {
		Vehicle firstVehicle = new Vehicle("B 10 IOS", 100000.0, 2020, MileageUnit.KM);

		VehicleRepository repository = new VehicleRepository();
		repository.addVehicle(firstVehicle);
	
		for (int i = 0; i < repository.getNumberOfVehicles(); i++) {
			Vehicle v = repository.getVehicleAtPosition(i);
			v.printVehicleDetails();
		}
	}
}
