const cars = [
  { id: 'E01', model: 'Tata Nexon EV', brand: 'Tata', fuel: 'EV', rent: 15000 },
  { id: 'N01', model: 'Maruti Swift', brand: 'Maruti', fuel: 'Petrol', rent: 8000 },
  { id: 'IE01', model: 'Tesla Model 3', brand: 'Tesla', fuel: 'EV', rent: 50000 },
  { id: 'MG01', model: 'MG ZS EV', brand: 'MG', fuel: 'EV', rent: 29000 },
];

function renderCars() {
  const list = document.getElementById('carsList');
  if (!list) return;
  list.innerHTML = cars.map(c => `
    <div class="car">
      <h4>${c.model}</h4>
      <div><span class="badge">${c.fuel}</span> • ${c.brand}</div>
      <div style="margin-top:8px; font-weight:600;">Rs ${c.rent.toLocaleString()} / month</div>
      <button style="margin-top:10px;">Book</button>
    </div>
  `).join('');
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
