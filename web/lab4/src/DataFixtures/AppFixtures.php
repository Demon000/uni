<?php

namespace App\DataFixtures;

use App\Entity\AttributeType;
use App\Entity\City;
use App\Entity\Person;
use App\Entity\Product;
use App\Entity\ProductAttribute;
use App\Entity\Track;
use Doctrine\Bundle\FixturesBundle\Fixture;
use Doctrine\Common\Persistence\ObjectManager;

class AppFixtures extends Fixture {
    private ?ObjectManager $manager = null;

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
        $brandAttribute = $this->createAttributeType('brand');
        $storageAttribute = $this->createAttributeType('storage');
        $ramAttribute = $this->createAttributeType('ram');
        $colorAttribute = $this->createAttributeType('color');

        $mi9 = $this->createProduct('Xiaomi Mi9',
                'Xiaomi Mi 9, Dual SIM, 64GB, 6GB RAM, 4G, Blue', 2199);
        $this->createProductAttributes($mi9, [
                [$brandAttribute, 'Xiaomi'],
                [$storageAttribute, '64GB'],
                [$ramAttribute, '6GB RAM'],
                [$colorAttribute, 'Blue'],
        ]);

        $redmiNote8Pro = $this->createProduct('Xiaomi Redmi Note 8 Pro',
                'Xiaomi Redmi Note 8 Pro, Dual SIM, 64GB, 6GB RAM, 4G, Blue', 1099);
        $this->createProductAttributes($redmiNote8Pro, [
                [$brandAttribute, 'Xiaomi'],
                [$storageAttribute, '64GB'],
                [$ramAttribute, '6GB RAM'],
                [$colorAttribute, 'Blue'],
        ]);

        $miNote10Pro = $this->createProduct('Xiaomi Mi Note 10 Pro',
                'Xiaomi Mi Note 10 Pro, Dual SIM, 256GB, 8GB RAM, 4G, Midnight Black', 2699);
        $this->createProductAttributes($miNote10Pro, [
                [$brandAttribute, 'Xiaomi'],
                [$storageAttribute, '256GB'],
                [$ramAttribute, '8GB RAM'],
                [$colorAttribute, 'Midnight Black'],
        ]);

        $miNote10 = $this->createProduct('Xiaomi Mi Note 10',
                'Xiaomi Mi Note 10, Dual SIM, 128GB, 6GB RAM, 4G, Aurora Green', 2388);
        $this->createProductAttributes($miNote10, [
                [$brandAttribute, 'Xiaomi'],
                [$storageAttribute, '128GB'],
                [$ramAttribute, '6GB RAM'],
                [$colorAttribute, 'Aurora Green'],
        ]);

        $s10 = $this->createProduct('Samsung Galaxy S10',
                'Telefon mobil Samsung Galaxy S10, Dual SIM, 128GB, 8GB RAM, 4G, Green', 2999);
        $this->createProductAttributes($s10, [
                [$brandAttribute, 'Samsung'],
                [$storageAttribute, '128GB'],
                [$ramAttribute, '8GB RAM'],
                [$colorAttribute, 'Green'],
        ]);

        $a51 = $this->createProduct('Samsung Galaxy A51',
                'Telefon mobil Samsung Galaxy A51, Dual SIM, 128GB, 4GB RAM, 4G, Prism Blue', 1399);
        $this->createProductAttributes($a51, [
                [$brandAttribute, 'Samsung'],
                [$storageAttribute, '128GB'],
                [$ramAttribute, '4GB RAM'],
                [$colorAttribute, 'Prism Blue'],
        ]);
    }

    private function createAttributeType(string $name) {
        $attributeType = new AttributeType();
        $attributeType->setName($name);
        $this->manager->persist($attributeType);
        return $attributeType;
    }

    public function createProduct(string $name, string $description, int $price) {
        $product = new Product();
        $product->setName($name);
        $product->setDescription($description);
        $product->setPrice($price);
        $this->manager->persist($product);
        return $product;
    }

    public function createProductAttributes($product, array $attributes) {
        foreach ($attributes as $attribute) {
            assert(count($attribute) == 2);
            $attributeType = $attribute[0];
            $attributeValue = $attribute[1];
            $this->createProductAttribute($product, $attributeType, $attributeValue);
        }
    }

    private function createProductAttribute($product, $attributeType, $value) {
        $productAttribute = new ProductAttribute();
        $productAttribute->setProduct($product);
        $productAttribute->setAttributeType($attributeType);
        $productAttribute->setValue($value);
        $this->manager->persist($productAttribute);
        return $productAttribute;
    }
}
