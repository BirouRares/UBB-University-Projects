import express from "express";
import bodyParser from "body-parser";
import cors from "cors";
import carRoutes from "./routes/cars.js";

const app = express();
const port=5000;

app.use(bodyParser.json());
app.use(cors());

app.use("/", carRoutes);

app.get("/", (req, res) => res.send("Hello World!"));
app.all("*", (req, res) => res.send("That Route does not exists!"));

app.listen(port, () => {
  console.log(`Server is running on port: http://localhost:${port}`);
});