-- phpMyAdmin SQL Dump
-- version 5.0.2
-- https://www.phpmyadmin.net/
--
-- Hôte : 127.0.0.1:3306
-- Généré le : lun. 06 déc. 2021 à 22:45
-- Version du serveur :  5.7.31
-- Version de PHP : 7.3.21

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de données : `sac`
--

-- --------------------------------------------------------

--
-- Structure de la table `arbre`
--

DROP TABLE IF EXISTS `arbre`;
CREATE TABLE IF NOT EXISTS `arbre` (
  `NomBois` varchar(50) NOT NULL,
  `IdBois` int(11) NOT NULL AUTO_INCREMENT,
  `TypeBois` varchar(50) NOT NULL,
  `OrigineBois` varchar(50) NOT NULL,
  `TmpSechage` int(50) NOT NULL,
  `TempMin` int(50) NOT NULL,
  PRIMARY KEY (`IdBois`)
) ENGINE=MyISAM AUTO_INCREMENT=4 DEFAULT CHARSET=latin1;

--
-- Déchargement des données de la table `arbre`
--

INSERT INTO `arbre` (`NomBois`, `IdBois`, `TypeBois`, `OrigineBois`, `TmpSechage`, `TempMin`) VALUES
('Sapin', 1, 'Dur', 'Nord', 6, 15),
('Erable', 2, 'Dur', 'Nord-Equateur', 6, 18),
('Chêne', 3, 'Dur', 'Europe', 10, 20);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
