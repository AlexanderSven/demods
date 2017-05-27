﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using DSCoreWrapper;

namespace Aquarius
{
    public partial class HierarchyComponents : Form
    {
        List<DSClassifierWrapper> classifiers_ = new List<DSClassifierWrapper>();
        DSHierarchyWrapper hierarchy_ = new DSHierarchyWrapper();
        public HierarchyComponents(DSHierarchyWrapper hierarchy)
        {
            InitializeComponent();
            hierarchy_ = hierarchy;
        }

        private void HierarchyComponents_Load(object sender, EventArgs e)
        {
            RefreshClassifiers();
        }
        private void RefreshClassifiers()
        {
            classifiers_.Clear();
            listBox1.Items.Clear();
            classifiers_ = hierarchy_.getClassifiers();
            foreach (DSClassifierWrapper cl in classifiers_)
            {
                listBox1.Items.Add(cl.getName() + "." + cl.getType());
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Form f = new Classifier(hierarchy_);
            f.Show();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Form f = new Classifier(hierarchy_, classifiers_[listBox1.SelectedIndex]);
            f.Show();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            hierarchy_.removeClassifier(classifiers_[listBox1.SelectedIndex].getID());
            RefreshClassifiers();
        }
    }
}