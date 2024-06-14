document.addEventListener('DOMContentLoaded', function() {
    const randomizeArmorBtn = document.getElementById('randomize-armor-btn');
    const randomizeHelmBtn = document.getElementById('randomize-helm-btn');
    const randomizeWeaponBtn = document.getElementById('randomize-weapon-btn');

    randomizeArmorBtn.addEventListener('click', function() {
      document.getElementById('armor-result').textContent = getRandomEquipmentItem('Armor');
    });

    randomizeHelmBtn.addEventListener('click', function() {
      document.getElementById('helm-result').textContent = getRandomEquipmentItem('Helm');
    });

    randomizeWeaponBtn.addEventListener('click', function() {
      document.getElementById('weapon-result').textContent = getRandomEquipmentItem('Weapon');
    });

    function getRandomEquipmentItem(slot) {
      const prefixes = ['Normal', 'Polished', 'Divine', 'Dwarven', 'Draconic']; // Replace with your list of prefixes
      const suffixes = [' of Evil', ' touched by the Blessed Mother', ' of Infinite Wisdom', " of Giant's Strength", ' of Shadowwalker\'s Stride', ' witnessed by the Old One', 'of the tiny toddlers might']; // Replace with your list of suffixes

      const randomPrefix = prefixes[Math.floor(Math.random() * prefixes.length)];
      const randomSuffix = suffixes[Math.floor(Math.random() * suffixes.length)];

      return `${randomPrefix} ${slot}${randomSuffix}`;
    }
  });

