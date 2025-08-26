const cars = [
  { id: 'F01', model: 'Ferrari LaFerrari', brand: 'Ferrari', fuel: 'Petrol', rent: 250000, image: 'Car1.jpg', year: 2013, engine: 'V12', horsepower: 950 },
  { id: 'L01', model: 'Lamborghini Aventador', brand: 'Lamborghini', fuel: 'Petrol', rent: 200000, image: 'car2.jpg', year: 2011, engine: 'V12', horsepower: 700 },
  { id: 'M01', model: 'Mercedes-AMG GT', brand: 'Mercedes-Benz', fuel: 'Petrol', rent: 180000, image: 'car3.jpg', year: 2014, engine: 'V8 BiTurbo', horsepower: 520 },
  { id: 'M02', model: 'Mercedes-AMG GT R', brand: 'Mercedes-Benz', fuel: 'Petrol', rent: 210000, image: 'car4.jpg', year: 2017, engine: 'V8 BiTurbo', horsepower: 585 },
  { id: 'C01', model: 'Chevrolet Corvette Z06', brand: 'Chevrolet', fuel: 'Petrol', rent: 170000, image: 'car5.jpg', year: 2015, engine: 'V8 Supercharged', horsepower: 650 },
  { id: 'A01', model: 'Audi R8', brand: 'Audi', fuel: 'Petrol', rent: 195000, image: 'car6.jpg', year: 2015, engine: 'V10', horsepower: 610 },
  { id: 'B01', model: 'BMW M4', brand: 'BMW', fuel: 'Petrol', rent: 120000, image: 'car7.jpg', year: 2014, engine: 'Inline 6', horsepower: 425 },
  { id: 'M03', model: 'Mercedes-AMG GT Black Series', brand: 'Mercedes-Benz', fuel: 'Petrol', rent: 280000, image: 'car8.jpg', year: 2020, engine: 'V8 BiTurbo', horsepower: 730 },
];

function createCarCard(c, index) {
  const card = document.createElement('div');
  card.className = 'car-card';
  card.style.animationDelay = `${index * 0.1}s`;
  card.innerHTML = `
    <img src="${c.image}" alt="${c.brand} ${c.model}">
    <div class="car-card-content">
      <h4>${c.brand} ${c.model}</h4>
      <div class="details">
        <span class="badge">${c.fuel}</span> • ${c.year}
      </div>
      <div class="details">
        ${c.engine} • ${c.horsepower} hp
      </div>
      <div class="rent">Rs ${c.rent.toLocaleString()} / month</div>
      <button class="btn-primary" style="width: 100%;">Book Now</button>
    </div>
  `;
  return card;
}

function renderCars() {
  const featuredCars = cars.filter(c => ['F01', 'L01', 'M03'].includes(c.id));
  const otherCars = cars.filter(c => !['F01', 'L01', 'M03'].includes(c.id));

  const featuredList = document.getElementById('featuredCars');
  if (featuredList) {
    featuredList.innerHTML = '';
    featuredCars.forEach((c, index) => {
      const card = createCarCard(c, index);
      featuredList.appendChild(card);
    });
  }

  const list = document.getElementById('carsList');
  if (list) {
    list.innerHTML = '';
    otherCars.forEach((c, index) => {
      const card = createCarCard(c, index);
      list.appendChild(card);
    });
  }

  const observer = new IntersectionObserver((entries, observer) => {
    entries.forEach(entry => {
      if (entry.isIntersecting) {
        entry.target.classList.add('is-visible');
        observer.unobserve(entry.target);
      }
    });
  }, {
    threshold: 0.2
  });

  document.querySelectorAll('.car-card').forEach(card => {
    observer.observe(card);
  });
}

function attachEvents() {
  const btn = document.getElementById('viewCarsBtn');
  if (btn) {
    btn.addEventListener('click', () => {
      document.getElementById('cars')?.scrollIntoView({ behavior: 'smooth' });
    });
  }
  const year = document.getElementById('year');
  if (year) year.textContent = String(new Date().getFullYear());
}

window.addEventListener('DOMContentLoaded', () => {
  renderCars();
  attachEvents();
});
