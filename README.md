# Cytis

## Un aparat telecomandat pentru modificarea presiunii la biciclete

## Rezumat

De câte ori ai mers la o tură cu bicicleta și ai uitat să îți verifici presiunea din roți înainte de a pleca? Sau Poate ai decis să o iei pe macadam când aveai în plan doar asfalt lin și te-ai cam zdruncinat. Dacă ai pățit acestea, ei bine, Cytis îți poate veni în ajutor, dându-ți posibiliatea de a-ți regla presiunea direct de la telefon, sau orice dispozitiv cu bluetooth, acesta așteptând comenzile tale pe butucul roții. Din când în când va trebui schimbată canistra de aer.

## Din ce este Cytis compus?

Pentru început, acest proiect are două jumătăți: interfața web și dispozitivul în sine. Interfața web este construită în Ruby on Rails și configurată ca un Progressive Web App, pentru a putea fi instalată. Pe site este posibilă creearea unui cont(pentru autentificare am folosit Devise). Comunicarea este realizată folosind tehnologia Web Bluetooth. Dispozitivul este bazat pe un Arduino Nano cuplat cu un modul HM-10 pentru bluetooth. aerul de intrare este preluat dintr-o canistră de CO2, iar întreaga instalație este montată pe butucul roții pentru a încurca mai puțin.

**Proiectul se află în stadiul de prototip, o variantă de producție fiind mult mai mică și mai fiabilă, însă am fost limitat de buget**

## Cele patru lucruri principale pe care le face

- Procesează comenzile de la interfața web
- Citește presiunea actuală
- Umflă cauciucul
- Dezumflă cauciucul

## Tehnologii utilizate

- Arduino - partea fizică
- Ruby on Rails - backend-ul interfeței web
- HTML, CSS, JS - frontend-ul interfeței web
- Web Bluetooth - comunicarea cu dispozitivul fizic - limitează browserul ce poate fi utilizat
- PWA - permite instalarea site-ului

## Cerințe de Sistem

- Dispozitiv cu bluetooth, care poate accesa Internetul folosind Chrome(sau derivat) sau Opera

## Dorești să rulezi interfața web local?

- Ai nevoie de Ruby on Rails `v6.1.4` și Ruby `v3.0.3` instalat
- Rulează `git clone git@github.com:sipandrei/Cytis_frontend.git`
- Rulează `bundle install`
- Rulează `rails db:migrate`
- Pornește serverul și ar trebui să ai o interfață web Cytis ce rulează local
