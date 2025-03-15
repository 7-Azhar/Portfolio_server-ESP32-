#include <WiFi.h>
#include <WebServer.h>

// WiFi credentials - replace with your network details
const char* ssid = "Galaxy";
const char* password = "Milkyway";

// Create web server on port 80
WebServer server(80);

// HTML content for the portfolio website - optimized for ESP32
const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Mohammed Azhar Hussain - Portfolio</title>
  <!-- This is just the JavaScript and related HTML modifications to add to your existing code -->

<!-- Add this inside your <head> tag, after your CSS -->
<script>
  document.addEventListener('DOMContentLoaded', function() {
    // 1. Mobile Navigation Toggle
    const mobileNavToggle = document.createElement('div');
    mobileNavToggle.className = 'mobile-nav-toggle';
    mobileNavToggle.innerHTML = '&#9776;';
    document.querySelector('header .container').prepend(mobileNavToggle);
    
    mobileNavToggle.addEventListener('click', function() {
      const contactInfo = document.querySelector('.contact-info');
      contactInfo.classList.toggle('active');
    });
    
    // 2. Project Filter System
    const filterContainer = document.createElement('div');
    filterContainer.className = 'project-filters';
    filterContainer.innerHTML = `
      <span class="filter-label">Filter Projects:</span>
      <button class="filter-btn active" data-filter="all">All</button>
      <button class="filter-btn" data-filter="Full-Stack">Full-Stack</button>
      <button class="filter-btn" data-filter="Front-End">Front-End</button>
      <button class="filter-btn" data-filter="Back-End">Back-End</button>
    `;
    document.querySelector('.projects-grid').before(filterContainer);
    
    const filterButtons = document.querySelectorAll('.filter-btn');
    const projectCards = document.querySelectorAll('.project-card');
    
    filterButtons.forEach(button => {
      button.addEventListener('click', function() {
        // Remove active class from all buttons
        filterButtons.forEach(btn => btn.classList.remove('active'));
        // Add active class to clicked button
        this.classList.add('active');
        
        const filterValue = this.getAttribute('data-filter');
        
        projectCards.forEach(card => {
          // If "All" is selected or card contains the tag
          if (filterValue === 'all' || card.querySelector('.project-tags').textContent.includes(filterValue)) {
            card.style.display = 'block';
          } else {
            card.style.display = 'none';
          }
        });
      });
    });
    
    // 3. Skill Progress Animation
    const skillTags = document.querySelectorAll('.skill-tag');
    
    // Create an observer for animations
    const observer = new IntersectionObserver((entries) => {
      entries.forEach(entry => {
        if (entry.isIntersecting) {
          setTimeout(() => {
            entry.target.classList.add('animate');
          }, Math.random() * 500); // Random delay for nicer effect
          observer.unobserve(entry.target);
        }
      });
    }, { threshold: 0.1 });
    
    // Observe each skill tag
    skillTags.forEach(tag => {
      observer.observe(tag);
    });
    
    // 4. Theme Switcher
    const themeToggle = document.createElement('button');
    themeToggle.className = 'theme-toggle';
    themeToggle.textContent = '☀️';
    themeToggle.title = 'Toggle light/dark mode';
    document.querySelector('header .container').appendChild(themeToggle);
    
    // Check for saved theme preference
    const savedTheme = localStorage.getItem('portfolioTheme');
    if (savedTheme === 'light') {
      document.body.classList.add('light-theme');
      themeToggle.textContent = '🌙';
    }
    
    themeToggle.addEventListener('click', function() {
      document.body.classList.toggle('light-theme');
      
      if (document.body.classList.contains('light-theme')) {
        localStorage.setItem('portfolioTheme', 'light');
        themeToggle.textContent = '🌙';
      } else {
        localStorage.setItem('portfolioTheme', 'dark');
        themeToggle.textContent = '☀️';
      }
    });
    
    // 5. Certification Accordion
    const certTitles = document.querySelectorAll('.cert-title');
    
    certTitles.forEach(title => {
      title.addEventListener('click', function() {
        const details = this.nextElementSibling;
        const isExpanded = details.style.maxHeight;
        
        // Close all other open details
        document.querySelectorAll('.cert-details').forEach(item => {
          item.style.maxHeight = null;
        });
        
        // Toggle this one
        if (!isExpanded) {
          details.style.maxHeight = details.scrollHeight + 'px';
          this.classList.add('expanded');
        } else {
          this.classList.remove('expanded');
        }
      });
    });
  });
</script>

<!-- Add these CSS rules to your existing stylesheet -->
<style>
  /* Mobile Navigation */
  .mobile-nav-toggle {
    display: none;
    font-size: 1.8rem;
    cursor: pointer;
    position: absolute;
    top: 20px;
    right: 20px;
    color: var(--gold);
    transition: transform 0.3s;
  }
  
  /* Project Filters */
  .project-filters {
    display: flex;
    gap: 10px;
    margin-bottom: 20px;
    flex-wrap: wrap;
    align-items: center;
  }
  
  .filter-label {
    color: var(--gold-light);
    font-size: 0.9rem;
  }
  
  .filter-btn {
    background: transparent;
    border: 1px solid var(--gold);
    color: var(--text-light);
    padding: 5px 12px;
    border-radius: 4px;
    cursor: pointer;
    transition: all 0.3s;
    font-size: 0.9rem;
  }
  
  .filter-btn.active, .filter-btn:hover {
    background-color: var(--gold);
    color: var(--dark-bg);
  }
  
  /* Skill Animation */
  .skill-tag {
    opacity: 0;
    transform: translateY(10px);
    transition: all 0.5s ease;
  }
  
  .skill-tag.animate {
    opacity: 1;
    transform: translateY(0);
  }
  
  /* Theme Switcher */
  .theme-toggle {
    position: absolute;
    top: 20px;
    left: 20px;
    background: transparent;
    border: none;
    font-size: 1.5rem;
    cursor: pointer;
    opacity: 0.8;
    transition: opacity 0.3s;
  }
  
  .theme-toggle:hover {
    opacity: 1;
  }
  
  /* Light Theme */
  .light-theme {
    --dark-bg: #f0f0f0;
    --dark-card: #ffffff;
    --text-light: #333333;
  }
  
  .light-theme h1 {
    background: var(--gold);
    -webkit-background-clip: text;
    background-clip: text;
  }
  
  /* Certification Accordion */
  .cert-title {
    cursor: pointer;
    position: relative;
    padding-right: 30px;
  }
  
  .cert-title::after {
    content: '+';
    position: absolute;
    right: 10px;
    transition: transform 0.3s;
  }
  
  .cert-title.expanded::after {
    transform: rotate(45deg);
  }
  
  .cert-details {
    max-height: 0;
    overflow: hidden;
    transition: max-height 0.3s ease;
  }
  
  /* Responsive design additions */
  @media (max-width: 768px) {
    .mobile-nav-toggle {
      display: block;
    }
    
    .contact-info {
      display: none;
      flex-direction: column;
      width: 100%;
    }
    
    .contact-info.active {
      display: flex;
    }
  }
</style>
  <style>
    :root {
      --gold: #d4af37;
      --gold-light: #f2d57e;
      --dark-bg: #121212;
      --dark-card: #1e1e1e;
      --text-light: #f5f5f5;
    }
    
    * {
      margin: 0;
      padding: 0;
      box-sizing: border-box;
      font-family: Arial, sans-serif;
    }
    
    body {
      background-color: var(--dark-bg);
      color: var(--text-light);
      line-height: 1.6;
    }
    
    .container {
      width: 90%;
      max-width: 1200px;
      margin: 0 auto;
      padding: 20px 0;
    }
    
    /* Header Section */
    header {
      text-align: center;
      padding: 40px 0 20px;
      background: linear-gradient(135deg, var(--dark-bg), var(--dark-card));
      border-bottom: 2px solid var(--gold);
    }
    
    .header-content {
      display: flex;
      flex-direction: column;
      align-items: center;
    }
    
    h1 {
      font-size: 2.5rem;
      margin-bottom: 10px;
      background: linear-gradient(to right, var(--gold), var(--gold-light), var(--gold));
      -webkit-background-clip: text;
      -webkit-text-fill-color: transparent;
      background-clip: text;
    }
    
    .title {
      font-size: 1.2rem;
      margin-bottom: 15px;
      color: var(--gold-light);
    }
    
    .contact-info {
      display: flex;
      flex-wrap: wrap;
      justify-content: center;
      gap: 15px;
      margin: 15px 0;
    }
    
    .contact-info a {
      color: var(--text-light);
      text-decoration: none;
      padding: 5px 10px;
      border-radius: 5px;
      background-color: rgba(212, 175, 55, 0.2);
      transition: background-color 0.3s;
    }
    
    .contact-info a:hover {
      background-color: rgba(212, 175, 55, 0.4);
    }
    
    /* Skills Section */
    .section {
      margin: 30px 0;
      padding: 20px;
      background-color: var(--dark-card);
      border-radius: 8px;
      box-shadow: 0 4px 8px rgba(0, 0, 0, 0.3);
      border-left: 3px solid var(--gold);
    }
    
    h2 {
      font-size: 1.8rem;
      margin-bottom: 20px;
      color: var(--gold);
      position: relative;
    }
    
    h2::after {
      content: '';
      position: absolute;
      bottom: -5px;
      left: 0;
      width: 50px;
      height: 3px;
      background: linear-gradient(to right, var(--gold), transparent);
    }
    
    .skills-container {
      display: grid;
      grid-template-columns: repeat(auto-fill, minmax(300px, 1fr));
      gap: 20px;
    }
    
    .skill-category {
      margin-bottom: 15px;
    }
    
    .skill-category h3 {
      font-size: 1.2rem;
      margin-bottom: 10px;
      color: var(--gold-light);
    }
    
    .skill-list {
      display: flex;
      flex-wrap: wrap;
      gap: 8px;
    }
    
    .skill-tag {
      background: linear-gradient(45deg, rgba(212, 175, 55, 0.1), rgba(242, 213, 126, 0.2));
      border: 1px solid rgba(212, 175, 55, 0.3);
      border-radius: 4px;
      padding: 5px 10px;
      font-size: 0.9rem;
    }
    
    /* Projects Section */
    .projects-grid {
      display: grid;
      grid-template-columns: repeat(auto-fill, minmax(300px, 1fr));
      gap: 25px;
    }
    
    .project-card {
      background-color: rgba(30, 30, 30, 0.8);
      border-radius: 8px;
      overflow: hidden;
      transition: transform 0.3s, box-shadow 0.3s;
      border: 1px solid rgba(212, 175, 55, 0.2);
    }
    
    .project-card:hover {
      transform: translateY(-5px);
      box-shadow: 0 10px 20px rgba(0, 0, 0, 0.4);
    }
    
    .project-content {
      padding: 20px;
    }
    
    .project-title {
      font-size: 1.4rem;
      margin-bottom: 10px;
      color: var(--gold);
    }
    
    .project-tags {
      display: flex;
      flex-wrap: wrap;
      gap: 5px;
      margin-bottom: 15px;
    }
    
    .project-tag {
      background-color: rgba(212, 175, 55, 0.15);
      color: var(--gold-light);
      padding: 3px 8px;
      border-radius: 3px;
      font-size: 0.8rem;
    }
    
    .project-description {
      margin-bottom: 15px;
      font-size: 0.95rem;
    }
    
    /* Certifications Section */
    .cert-list {
      display: flex;
      flex-direction: column;
      gap: 15px;
    }
    
    .cert-item {
      padding: 15px;
      background-color: rgba(30, 30, 30, 0.6);
      border-radius: 6px;
      border-left: 3px solid var(--gold);
    }
    
    .cert-title {
      font-size: 1.1rem;
      color: var(--gold-light);
      margin-bottom: 5px;
    }
    
    .cert-details {
      font-size: 0.9rem;
      color: rgba(245, 245, 245, 0.8);
    }
    
    /* Additional Info Section */
    .additional-info {
      display: grid;
      grid-template-columns: repeat(auto-fill, minmax(250px, 1fr));
      gap: 20px;
    }
    
    .info-category h3 {
      font-size: 1.2rem;
      margin-bottom: 10px;
      color: var(--gold-light);
    }
    
    .info-list {
      list-style-type: none;
    }
    
    .info-list li {
      margin-bottom: 8px;
      display: flex;
      align-items: center;
    }
    
    .info-list li:before {
      content: '•';
      color: var(--gold);
      margin-right: 8px;
    }
    
    /* Footer */
    footer {
      text-align: center;
      padding: 20px 0;
      margin-top: 40px;
      border-top: 1px solid rgba(212, 175, 55, 0.3);
      font-size: 0.9rem;
      color: rgba(245, 245, 245, 0.7);
    }
    
    /* Responsive Design */
    @media (max-width: 768px) {
      h1 {
        font-size: 2rem;
      }
      
      .contact-info {
        flex-direction: column;
        align-items: center;
        gap: 10px;
      }
      
      .skills-container,
      .projects-grid,
      .additional-info {
        grid-template-columns: 1fr;
      }
    }
  </style>
</head>
<body>
  <header>
    <div class="container">
      <div class="header-content">
        <h1>MOHAMMED AZHAR HUSSAIN</h1>
        <p class="title">B.Tech, Computer Science Engineering with IoT</p>
        <p>VNRVJIET, Hyderabad</p>
        <div class="contact-info">
          <a href="mailto:mohammedazharhussain7105@gmail.com">mohammedazharhussain7105@gmail.com</a>
          <a href="https://github.com/" target="_blank">GitHub</a>
          <a href="https://linkedin.com/" target="_blank">LinkedIn</a>
          <a href="tel:+918885474081">+91 8885474081</a>
        </div>
      </div>
    </div>
  </header>

  <main class="container">
    <!-- Technical Skills -->
    <section class="section">
      <h2>TECHNICAL SKILLS</h2>
      <div class="skills-container">
        <div class="skill-category">
          <h3>Programming Languages</h3>
          <div class="skill-list">
            <span class="skill-tag">Java</span>
            <span class="skill-tag">Python</span>
            <span class="skill-tag">C</span>
            <span class="skill-tag">C++</span>
            <span class="skill-tag">JavaScript</span>
          </div>
        </div>
        
        <div class="skill-category">
          <h3>Web Development</h3>
          <div class="skill-list">
            <span class="skill-tag">HTML</span>
            <span class="skill-tag">CSS</span>
            <span class="skill-tag">Next.js</span>
            <span class="skill-tag">MERN Stack</span>
            <span class="skill-tag">Tailwind</span>
            <span class="skill-tag">Bootstrap</span>
            <span class="skill-tag">Material UI</span>
          </div>
        </div>
        
        <div class="skill-category">
          <h3>Database Systems</h3>
          <div class="skill-list">
            <span class="skill-tag">MongoDB</span>
            <span class="skill-tag">SQL</span>
            <span class="skill-tag">MySQL</span>
          </div>
        </div>
        
        <div class="skill-category">
          <h3>Tools & Technologies</h3>
          <div class="skill-list">
            <span class="skill-tag">Git</span>
            <span class="skill-tag">GitHub</span>
            <span class="skill-tag">VS Code</span>
            <span class="skill-tag">Postman</span>
            <span class="skill-tag">Docker</span>
            <span class="skill-tag">Implement</span>
          </div>
        </div>
        
        <div class="skill-category">
          <h3>Methodologies</h3>
          <div class="skill-list">
            <span class="skill-tag">Agile</span>
            <span class="skill-tag">Scrum</span>
            <span class="skill-tag">CI/CD</span>
            <span class="skill-tag">Test-Driven Development</span>
            <span class="skill-tag">Collaborative</span>
            <span class="skill-tag">Fast-Paced</span>
          </div>
        </div>
        
        <div class="skill-category">
          <h3>Soft Skills</h3>
          <div class="skill-list">
            <span class="skill-tag">Technical writing</span>
            <span class="skill-tag">Team collaboration</span>
            <span class="skill-tag">Problem-solving</span>
            <span class="skill-tag">Time Management</span>
          </div>
        </div>
      </div>
    </section>

    <!-- Projects -->
    <section class="section">
      <h2>PROJECTS</h2>
      <div class="projects-grid">
        <div class="project-card">
          <div class="project-content">
            <h3 class="project-title">Full-Stack E-commerce Platform</h3>
            <div class="project-tags">
              <span class="project-tag">MERN Stack</span>
              <span class="project-tag">Scalability</span>
              <span class="project-tag">Web Development</span>
            </div>
            <div class="project-description">
              <p>Built a collaborative e-commerce platform using MongoDB, Express.js, React, and Node.js</p>
              <p>Implemented back-end optimizations reducing page load time by 35% through best practices</p>
            </div>
          </div>
        </div>
        
        <div class="project-card">
          <div class="project-content">
            <h3 class="project-title">IP Tracking System (Ongoing)</h3>
            <div class="project-tags">
              <span class="project-tag">Front-End</span>
              <span class="project-tag">Back-End</span>
              <span class="project-tag">Software Development</span>
            </div>
            <div class="project-description">
              <p>Created interactive dashboard visualizing geographical data with fast-paced response time</p>
              <p>Collaborated with team to implement efficient coding practices and software development</p>
            </div>
          </div>
        </div>
        
        <div class="project-card">
          <div class="project-content">
            <h3 class="project-title">Blog App</h3>
            <div class="project-tags">
              <span class="project-tag">Full-Stack</span>
              <span class="project-tag">Communication Skills</span>
              <span class="project-tag">Web Development</span>
            </div>
            <div class="project-description">
              <p>Built version control system implementing microservices architecture with best practices</p>
              <p>Improved system scalability by 40% using collaborative development approaches</p>
            </div>
          </div>
        </div>
      </div>
    </section>

    <!-- Certifications & Achievements -->
    <section class="section">
      <h2>CERTIFICATIONS & ACHIEVEMENTS</h2>
      <div class="cert-list">
        <div class="cert-item">
          <div class="cert-title">MERN Stack Development</div>
          <div class="cert-details">150-hour training by T. Rajesh (Wipro), January 2025.</div>
        </div>
        <div class="cert-item">
          <div class="cert-title">AWS Cloud Practitioner</div>
          <div class="cert-details">Amazon Web Services, October 2024.</div>
        </div>
        <div class="cert-item">
          <div class="cert-title">IoT and Embedded Systems</div>
          <div class="cert-details">Coursera (University of California, Irvine), June 2024.</div>
        </div>
        <div class="cert-item">
          <div class="cert-title">Data Structures and Algorithms</div>
          <div class="cert-details">GeeksforGeeks, March 2024.</div>
        </div>
      </div>
    </section>


    <!-- Additional Information -->
    <section class="section">
      <h2>ADDITIONAL INFORMATION</h2>
      <div class="additional-info">
        <div class="info-category">
          <h3>Languages</h3>
          <ul class="info-list">
            <li>English (Professional)</li>
            <li>Hindi (Native)</li>
            <li>Telugu (Native)</li>
            <li>Urdu (Fluent)</li>
          </ul>
        </div>
        <div class="info-category">
          <h3>Interests</h3>
          <ul class="info-list">
            <li>Internet of Things</li>
            <li>Cloud Computing</li>
            <li>Web Development</li>
            <li>Machine Learning</li>
          </ul>
        </div>
        <div class="info-category">
          <h3>Activities</h3>
          <ul class="info-list">
            <li>Technical Club Member</li>
            <li>Hackathon Participant</li>
            <li>Open Source Contributor</li>
            <li>Student Mentoring</li>
          </ul>
        </div>
      </div>
    </section>
  </main>

  <footer>
    <div class="container">
      <p>&copy; 2025 Mohammed Azhar Hussain. All rights reserved.</p>
      <p>Last updated: March 2025</p>
    </div>
  </footer>
</body>
</html>
)=====";

void handleRoot() {
  server.send(200, "text/html", MAIN_page);
}

void setup() {
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to WiFi. IP address: ");
  Serial.println(WiFi.localIP());

  // Define web server routes
  server.on("/", handleRoot);

  // Start server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}