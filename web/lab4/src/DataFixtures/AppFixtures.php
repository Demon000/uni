<?php

namespace App\DataFixtures;

use App\Entity\City;
use App\Entity\Person;
use App\Entity\Product;
use App\Entity\Track;
use Doctrine\Bundle\FixturesBundle\Fixture;
use Doctrine\Common\Persistence\ObjectManager;

class AppFixtures extends Fixture {
    private $manager = null;

    public function load(ObjectManager $manager) {
        $this->manager = $manager;

        $this->createTracks();
        $this->createPeople();
        $this->createProducts();

        $manager->flush();
    }

    public function createTracks() {
        $suceavaCity = $this->createCity('Suceava');
        $clujCity = $this->createCity('Cluj-Napoca');
        $iasiCity = $this->createCity('Iasi');
        $bucurestiCity = $this->createCity('Bucuresti');
        $timisoaraCity = $this->createCity('Timisoara');
        $craiovaCity = $this->createCity('Craiova');
        $brasovCity = $this->createCity('Brasov');

        $this->createTrack($suceavaCity, $iasiCity);
        $this->createTrack($suceavaCity, $clujCity);
        $this->createTrack($suceavaCity, $bucurestiCity);
        $this->createTrack($iasiCity, $bucurestiCity);
        $this->createTrack($brasovCity, $timisoaraCity);
        $this->createTrack($brasovCity, $craiovaCity);
        $this->createTrack($bucurestiCity, $brasovCity);
    }

    /**
     * @param string $name
     * @return City
     */
    public function createCity(string $name) {
        $city = new City();
        $city->setName($name);
        $this->manager->persist($city);
        return $city;
    }

    /**
     * @param City $fromCity
     * @param City $toCity
     * @return Track
     */
    public function createTrack(City $fromCity, city $toCity): Track {
        $track = new Track();
        $track->setFromCity($fromCity);
        $track->setToCity($toCity);
        $this->manager->persist($track);
        return $track;
    }

    public function createPeople() {
        $this->createPerson('Cosmin', 'Tanislav', '+40757473994', 'cozzmy13@gmail.com');
        $this->createPerson('Mihai', 'Solcan', '+40723443994', 'solcanmihai@gmail.com');
        $this->createPerson('Teodor', 'Spiridon', '+40123453994', 'spirit@gmail.com');

        $this->createPerson('Christian', 'Tatoiu', '+40768412903', 'christa@gmail.com');
        $this->createPerson('Radu', 'Stefanescu', '+40799999903', 'stefradu@gmail.com');
        $this->createPerson('Silvia', 'Suciu', '+40799999999', 'ssilvia@gmail.com');

        $this->createPerson('Alexandra', 'Suciu', '+40799111999', 'salex@gmail.com');
        $this->createPerson('Nicu', 'Serte', '+40248219421', 'serten@gmail.com');
        $this->createPerson('Andreea', 'Vrabie', '+40765289519', 'birdie@gmail.com');

        $this->createPerson('Catalin', 'Vancea', '+07652849519', 'vcatalin@gmail.com');
    }

    public function createPerson(string $first_name, string $last_name, string $phone, string $email): Person {
        $person = new Person();
        $person->setFirstName($first_name);
        $person->setLastName($last_name);
        $person->setPhone($phone);
        $person->setEmail($email);
        $this->manager->persist($person);
        return $person;
    }

    public function createProducts() {
        $this->createProduct('Xiaomi Mi9', 'Xiaomi Mi 9, Dual SIM, 64GB, 6GB RAM, 4G, Blue', 2199);
        $this->createProduct('Xiaomi Redmi Note 8 Pro', 'Xiaomi Redmi Note 8 Pro, Dual SIM, 64GB, 6GB RAM, 4G, Blue', 1099);
        $this->createProduct('Xiaomi Mi Note 10 Pro', 'Xiaomi Mi Note 10 Pro, Dual SIM, 256GB, 8GB RAM, 4G, Midnight Black', 2699);
        $this->createProduct('Xiaomi Mi Note 10', 'Xiaomi Mi Note 10, Dual SIM, 128GB, 6GB RAM, 4G, Aurora Green', 2388);
    }

    public function createProduct(string $name, string $description, int $price) {
        $product = new Product();
        $product->setName($name);
        $product->setDescription($description);
        $product->setPrice($price);
        $this->manager->persist($product);
        return $product;
    }
}
