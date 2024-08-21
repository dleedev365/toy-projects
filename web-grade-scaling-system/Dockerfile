# This image comes with Node.js and NPM already installed
FROM node:10

# Create a directory to hold the application code inside the image
WORKDIR /app

# intsall app dependencies using the npm binary
# npm version 4 or earlier doesn't generate package-lock.json
COPY package*.json ./

# Install production dependencies.
RUN npm install

# Copy local code to the container image.
COPY . .


EXPOSE 8080


# Run the web service on container startup.
CMD [ "node", "server.js" ]
